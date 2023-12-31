import java.io.*;
import java.net.Socket;

class DataFrame implements Serializable {
    public char info;
    public int sequenceNumber;

    DataFrame() {
    }

    DataFrame(char data, int sequenceNumber) {
        this.info = data;
        this.sequenceNumber = sequenceNumber;
    }
}

class Acknowledgement implements Serializable {
    public boolean ack;
    public int sequenceNumber;

    Acknowledgement() {
    }

    Acknowledgement(boolean ack, int sequenceNumber) {
        this.ack = ack;
        this.sequenceNumber = sequenceNumber;
    }
}

public class Client {

    public static void main(String[] args) {
        try {
            System.out.println("Client Started");
            Socket socket = new Socket("localhost", 12345);

            ObjectOutputStream objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
            ObjectInputStream objectInputStream = new ObjectInputStream(socket.getInputStream());

            int noOfBits = 16;
            int windowSize = 5;
            DataFrame[] data = new DataFrame[noOfBits];
            int left_ptr = 0;
            int right_ptr = 0;

            while (left_ptr < noOfBits) {
                while (right_ptr < noOfBits && (right_ptr - left_ptr) < windowSize) {
                    data[right_ptr] = new DataFrame((char) ('a' + right_ptr), right_ptr);
                    objectOutputStream.writeObject(data[right_ptr]);
                    System.out.println("Sent: " + data[right_ptr].info);
                    right_ptr++;

                }
                Acknowledgement ACK = (Acknowledgement) objectInputStream.readObject();
                if (ACK.ack) {
                    System.out.println("Acknowledgment received for Frame " + ACK.sequenceNumber);
                    left_ptr++;
                } else {
                    System.out.println("NACK received for Frame " + ACK.sequenceNumber + ". Retransmitting.");
                    int resendIndex = ACK.sequenceNumber;
                    objectOutputStream.writeObject(data[resendIndex]);
                    System.out.println("Sent (Retransmit): " + data[resendIndex].info);
                }

            }
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
