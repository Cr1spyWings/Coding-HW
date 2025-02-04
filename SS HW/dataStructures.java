// declarations of different applications
public abstract class Computer {
  // attributes
  private String gpu;
  private String ram;
  private int version;
  private String screenSize;

  // methods
  public void update();
  public void download();
  public void accessInternet();

  // calling attributes
  public String getGPU();
  public String getRAM();
  public int getVersion();
}

public interface mobileDevice {
  public void installApp();
  public void charge();
  public void download();
  public void accessInternet();
}

public class Laptop extends Computer implements mobileDevice {
  // implemented functions
  public void installApp();
  public void charge();
  public void download();
  public void accessInternet();
  
}

public abstract class smartPhone extends Computer implements mobileDevice { 
  // attributes
  private String ringtone;
  
  // implemented functions
  public void installApp();
  public void charge();
  public void download();
  public void accessInternet();

  // phone functions
  public void call();
  public void text();
  
  // calling attributes
  public int getVersion();
  public int getScreenSize();
  public String getRingtone();
}

public class iPad extends smartPhone {
  public void splitScreen();
  public void slideOver();
  
}

public class smartWatch extends smartPhone {
  public void checkHeartRate();
  public void checkBP();
  public void checkSteps();
}

// main function
public class Main {
  public static void main(String[] args) {
    // defining the classes
    Laptop myLap("GTX 2700", "8GB DDR4", 11, "1920x1080");
    iPad myIpad();
    smartWatch myWatch();
    
    // array of the devices
    Computer[] devices = {myLap, myIpad, myWatch};
  }
}
