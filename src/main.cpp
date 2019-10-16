#include <iostream>
#include "../includes/config_reader.h"
#include "../includes/heatmap_creator.h"
#include "../includes/MpiTable.h"
#include <mpi.h>

#include <cmath>
#include <thread>
#include <iomanip>
#include <atomic>

#include <chrono>
#include <atomic>

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced ()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us (const D &d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

double f (double x1, double x2)
{
    double a = 20;
    double b = 0.2;
    double c = 2 * M_PI;
    return -a * exp(-b * sqrt(0.5 * (x1 * x1 + x2 * x2))) - exp(0.5 * (cos(c * x1) + cos(c * x2))) + a + exp(1);
}

double integral (double x_from, double x_to, double y_from, double y_to, double precision, std::atomic<double> &res)
{
    double local_res = 0;
    double x = x_from;
    while (x <= x_to) {
        double y = y_from;
        while (y <= y_to) {
            local_res += f(x, y);
            y += precision;
        }
        x += precision;
    }

    res = res + local_res;
}

double runner (double precission, double start_x, double end_x, double start_y, double end_y)
{
    std::atomic<double> res{0};

    integral(start_x, end_x, start_y, end_y, precission, std::ref(res));

    return res * precission * precission;
}

double calculateNewTemperature(double currentValue, ) {

}

int main(int argc, char *argv[]) {
    int commsize, rank, len;
    char procname[MPI_MAX_PROCESSOR_NAME];

    double prev = 99;
    double now = -99;
    double precision = 0.4;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(procname, &len);

    if (rank == 0) {

        auto start = get_current_time_fenced();

        config *c = new config("config.dat");

        double err_abs = c->get_double("err_abs");
        double err_rel = c->get_double("err_rel");
        double start_x = c->get_double("x_start");
        double end_x = c->get_double("x_end");
        double start_y = c->get_double("y_start");
        double end_y = c->get_double("y_end");

        double x = (end_x - start_x) / (commsize - 1);

        for (int i = 1; i < commsize; ++i) {
            double start_x_send = start_x + x * (i-1);
            double end_x_send = start_x + x * i;

            MPI_Send(&err_abs, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(&err_rel, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(&start_x_send, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(&end_x_send, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(&start_y, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(&end_y, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }

        double res = 0;

        for (int j = 1; j < commsize; ++j) {
            double recv_res;

            MPI_Recv(&recv_res, 1, MPI_DOUBLE, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            res += recv_res;
        }

        auto end = get_current_time_fenced();

        std::cout << "Res: " << std::setprecision(7) << res << std::endl;
        std::cout << "Time in us: " << to_us(end - start) << std::endl;
        std::cout << "Time in sec: " << to_us(end - start) / 1000000 << std::endl;
    }

    if (rank > 0) {

        double err_abs;
        double err_rel;
        double start_x;
        double end_x;
        double start_y;
        double end_y;

        MPI_Recv(&err_abs, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&err_rel, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&start_x, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&end_x, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&start_y, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&end_y, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        while (!(std::abs(prev - now) <= err_abs && std::abs(prev - now) / prev <= err_rel)) {
            precision /= 2;
            prev = now;
            now = runner(precision, start_x, end_x, start_y, end_y);
        }

        MPI_Send(&now, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}