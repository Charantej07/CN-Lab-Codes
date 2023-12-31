import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

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

public class Server {
    public static void main(String[] args) {
        try {
            System.out.println("Waiting for clients");
            ServerSocket ss = new ServerSocket(12345);
            Socket s = ss.accept();
            System.out.println("Client connected");

            ObjectInputStream objectInputStream = new ObjectInputStream(s.getInputStream());
            ObjectOutputStream objectOutputStream = new ObjectOutputStream(s.getOutputStream());

            Map<Integer, Boolean> explicitError = new HashMap<>();
            explicitError.put(3, true);
            explicitError.put(5, true);
            explicitError.put(15, true);
            int framesReceived = 0;
            while (framesReceived < 16) {
                DataFrame receivedFrame = (DataFrame) objectInputStream.readObject();
                framesReceived++;
                if (explicitError.containsKey(receivedFrame.sequenceNumber)
                        && explicitError.get(receivedFrame.sequenceNumber)) {
                    Acknowledgement ACK = new Acknowledgement(false, receivedFrame.sequenceNumber);
                    objectOutputStream.writeObject(ACK);
                    System.out.println("Sent NACK for " + receivedFrame.sequenceNumber);
                    explicitError.put(receivedFrame.sequenceNumber, false);
                    framesReceived--;
                } else {
                    System.out.println("Received: " + receivedFrame.info);
                    Acknowledgement ACK = new Acknowledgement(true, receivedFrame.sequenceNumber);
                    objectOutputStream.writeObject(ACK);
                    System.out.println("Sent Acknowledgement for " + receivedFrame.sequenceNumber);
                }

            }
        } catch (

        Exception e) {
            e.printStackTrace();
        }
    }
}
