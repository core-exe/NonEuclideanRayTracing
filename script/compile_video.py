#%%
import cv2

#%%
path_frames = "../output/demo3/"
n_frames = 1518
size = (400, 300)
frame_list = []
for i in range(n_frames):
    frame_list.append(cv2.imread(path_frames + "{:04d}.png".format(i)))

output_path = "../output/demo3/output.avi"
video_writer = cv2.VideoWriter(output_path, cv2.VideoWriter_fourcc(*'DIVX'), 24, size)

for frame in frame_list:
    video_writer.write(frame)

video_writer.release()
print("finished.")
# %%
