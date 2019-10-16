#include <iostream>
#include <ConfigReader.h>
#include "MpiTable.h"
#include "MpiManager.h"
#include "openmpi/mpi.h"
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

int main() {

        config *c = new config("config.dat");

//    ConfigReader c("../config.data");
//    int numThreads = c.get_int("num_threads");
//    int height = c.get_int("height");
//    int width = c.get_int("width");
//    MpiManager manager(numThreads,
//                       height,
//                       width,
//                       "test");
//
//    std::vector<double> table((height + 2)*(width + 2));
//    c.getTable(table);
//
//    for (int i = 0; i < numThreads; ++i) {
//        manager.splitData(i, table);
//    }
//
        double err_abs = c->get_double("err_abs");
        double err_rel = c->get_double("err_rel");
        double start_x = c->get_double("x_start");
        double end_x = c->get_double("x_end");
        double start_y = c->get_double("y_start");
        double end_y = c->get_double("y_end");



//    std::vector<double> top { 0,   1,   2,   3,   4,  5};
//    std::vector<double> vect{-1,  10,  20,  30,  40, -1,
//                             -1,  50,  60,  70,  80, -1,
//                             -1,  90, 100, 110, 120, -1,
//                             -1, 130, 140, 150, 160, -1,
//                             -1, 170, 180, 190, 200, -1};
//    std::vector<double> bot { -2,  -3,  -4, -5,  -6, -7};
//
//    auto a = MpiTable(4,5, vect);
//    a.setNeighbourTop(top);
//    a.setNeighbourBottom(bot);
//
//    c.getTable(table);

//
//    for (int i = 0; i < table.size(); ++i) {
//        std::cout << table[i] << std::endl;
//    }

//    std::cout << table.size() << std::endl;
//
//    std::vector<double> tt = a.getTop();
//    std::vector<double> tb = a.getBottom();
//    double x = 3.5;
//    a.set(1, 5, x);
//    a.flip();
//
//    tt = a.getTop();
//    tb = a.getBottom();
//
//    std::cout << a.get(1, 5) << std::endl;
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