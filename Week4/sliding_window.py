frame = input("Enter the frame: ")
frame_size = len(frame)
window_size = int(input("Enter the window size: "))

print("@Sender Side")

for i in range(window_size):
    print("Sent: ", i)

k = window_size
for j in range(frame_size+1):
    print("ACK received for: ", j)
    if k < frame_size+1:
        print("Sent: ", k)
        k += 1

print("@Receiver Side: ")
for i in range(frame_size+1):
    print("Received: ", i)
    print("Sent ACK for :", i)
