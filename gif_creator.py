from PIL import Image
import os

FOLDER = "./images"

frames = []

try:
    for file in sorted(os.listdir(FOLDER),  key=lambda x: int(x.split(".")[0])):
        img = Image.open(os.path.join(FOLDER, file))
        frames.append(img)
    frames[0].save('result.gif', format='GIF', append_images=frames[1:], save_all=True, duration=100, loop=0)
except ValueError:
    print("Maybe some non image files are in folder")