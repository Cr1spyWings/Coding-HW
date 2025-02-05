import java.util.*;
// Abstract class for different computer types
abstract class Computer {
  // Attributes
  private String gpu;
  private String ram;
  private int version;
  private String screenSize;

  // Constructor
  public Computer(String gpu, String ram, int version, String screenSize) {
    this.gpu = gpu;
    this.ram = ram;
    this.version = version;
    this.screenSize = screenSize;
  }

  // Abstract methods
  public abstract void update();
  public abstract void download();
  public abstract void accessInternet();

  // Getter methods
  public String getGPU() { return gpu; }
  public String getRAM() { return ram; }
  public int getVersion() { return version; }
  public String getScreenSize() { return screenSize; }
}

// Interface for mobile devices
interface MobileDevice {
  void installApp();
  void charge();
  void download();
  void accessInternet();
}

// Laptop class that extends Computer and implements MobileDevice
class Laptop extends Computer implements MobileDevice {
  public Laptop(String gpu, String ram, int version, String screenSize) {
    super(gpu, ram, version, screenSize);
  }

  @Override
  public void update() {
    System.out.println("Laptop updating...");
  }

  @Override
  public void download() {
    System.out.println("Laptop downloading...");
  }

  @Override
  public void accessInternet() {
    System.out.println("Laptop accessing internet...");
  }

  @Override
  public void installApp() {
    System.out.println("Installing app on laptop...");
  }

  @Override
  public void charge() {
    System.out.println("Laptop charging...");
  }
}

// SmartPhone class extending Computer and implementing MobileDevice
abstract class SmartPhone extends Computer implements MobileDevice {
  private String ringtone;

  public SmartPhone(String gpu, String ram, int version, String screenSize, String ringtone) {
    super(gpu, ram, version, screenSize);
    this.ringtone = ringtone;
  }

  @Override
  public void installApp() {
    System.out.println("Installing app on smartphone...");
  }

  @Override
  public void charge() {
    System.out.println("Smartphone charging...");
  }

  @Override
  public void download() {
    System.out.println("Smartphone downloading...");
  }

  @Override
  public void accessInternet() {
    System.out.println("Smartphone accessing internet...");
  }

  public void call() {
    System.out.println("Making a call...");
  }

  public void text() {
    System.out.println("Sending a text...");
  }

  public String getRingtone() { return ringtone; }
}

// iPad class extending SmartPhone
class iPad extends SmartPhone {
  public iPad(String gpu, String ram, int version, String screenSize, String ringtone) {
    super(gpu, ram, version, screenSize, ringtone);
  }
  
  @Override
    public void update() {
        System.out.println("Updating iPad with the latest iOS...");
    }

  public void splitScreen() {
    System.out.println("iPad using split screen...");
  }

  public void slideOver() {
    System.out.println("iPad using slide over...");
  }
}

// SmartWatch class extending SmartPhone
class SmartWatch extends SmartPhone {
  public SmartWatch(String gpu, String ram, int version, String screenSize, String ringtone) {
    super(gpu, ram, version, screenSize, ringtone);
  }
  
  @Override
    public void update() {
        System.out.println("Updating iPad with the latest iOS...");
    }

  public void checkHeartRate() {
    System.out.println("Checking heart rate...");
  }

  public void checkBP() {
    System.out.println("Checking blood pressure...");
  }

  public void checkSteps() {
    System.out.println("Checking steps...");
  }
}

// main function
public class dataStructures {
  public static void main(String[] args) {
    // create different objects
    Laptop laptop = new Laptop("NVIDIA", "16GB", 1, "15 inches");
    iPad ipad = new iPad("Apple A14", "8GB", 2, "10 inches", "Marimba");
    SmartWatch smartWatch = new SmartWatch("Snapdragon", "2GB", 3, "1.5 inches", "Beep Beep");

    // array
    Computer[] devicesArray = {laptop, ipad, smartWatch};

    // print devices from array
    System.out.println("Devices in Array:");
    for (Computer device : devicesArray) {
      System.out.println(device.getClass().getSimpleName() + " - GPU: " + device.getGPU());
    }
    System.out.println();

    // queue
    Queue<Computer> deviceQueue = new LinkedList<>();
    deviceQueue.add(laptop);
    deviceQueue.add(ipad);
    deviceQueue.add(smartWatch);

    // Dequeue operation
    System.out.println("Processing queue:");
    while (!deviceQueue.isEmpty()) {
      Computer device = deviceQueue.poll(); // Removes first element
      System.out.println("Dequeued: " + device.getClass().getSimpleName());
    }
    System.out.println();

    // linked list
    LinkedList<Computer> deviceList = new LinkedList<>();
    deviceList.add(laptop);
    deviceList.add(ipad);
    deviceList.add(smartWatch);

    System.out.println("Linked List Operations:");
    deviceList.removeFirst(); // Removes first element
    System.out.println("After removing first element: " + deviceList.getFirst().getClass().getSimpleName());
    System.out.println();

    // stack 
    Stack<Computer> deviceStack = new Stack<>();
    deviceStack.push(laptop);
    deviceStack.push(ipad);
    deviceStack.push(smartWatch);

    // Pop operation
    System.out.println("Processing stack:");
    while (!deviceStack.isEmpty()) {
      Computer device = deviceStack.pop(); // Removes top element
      System.out.println("Popped: " + device.getClass().getSimpleName());
    }
  }
}