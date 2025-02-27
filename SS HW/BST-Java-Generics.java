// Chris Wong
// BST & Java Generics

abstract class Shape {
  String name;

  int area();
  void toString();  
}

interface Comparable {
  // check if x's area is different from  y's to see if it should be added to BST
  boolean compareTo(Shape x, Shape y) {
    if(x.area() > y.area() || x.area() < y.area()) {
      return true;
    } else {
      return false;
    }
  }

  // checks for where in BST the shape should be place
  // always will run after compareTo as it moves through tree
  boolean compareArea(Shape x, Shape y) {
    if(x.area() > y.area()) {
      // tells to move y to left side of tree
      return true;
    } else {
      // tells to move y to right side of tree
      return false;
    }
  }
}

class Rectangle extends Shape implements Comparable {
  String name;
  int base;
  int height;

  // Consturctor
  public Rectangle(String name, int base, int height) {
    this.name = name;
    this.base = base;
    this.height = height;    
  }

  int area() {
    return base * height
  }

  void toString() {
    System.out.println("Rectangle " + name + ". Area: " + area(base, height));
  }
  
  // methods to allow for easy base & height grabs
  int getBase() {
    return base;
  }
  int getHeight() {
    return height'
  }
}

class Square extends Rectangle implements Comparable{
  String name;
  int base;
  int height;

  // Consturctor
  public Square(String name, int base, int height) {
    this.name = name;
    this.base = base;
    this.height = height;
  }

  int area() {
    return base * height
  }

  void toString() {
    System.out.println("Square " + name + ". Area: " + area(base, height));
  }
  
  // methods to allow for easy base & height grabs
  int getBase() {
    return base;
  }
  int getHeight() {
    return height'
  }
}

class Triangle extends Shape implements Comparable{
  String name;
  int base;
  int height;

  // Consturctor
  public Triangle(String name, int base, int height) {
    this.name = name;
    this.base = base;
    this.height = height;    
  }
  
  int area() {
    return (base * height) / 2;
  }

  void toString() {
    System.out.println("Triangle " + name + ". Area: " + area(base, height));
  }
  
  // methods to allow for easy base & height grabs
  int getBase() {
    return base;
  }
  int getHeight() {
    return height'
  }
}

class Circle extends Shape implements Comparable{
  String name;
  int radius;

  // Consturctor
  public Circle(String name, int radius) {
    this.name = name;
    this.radius = radius;
  }

  int area() {
    return Math.pow(radius, 2) * 3.14 // using 3.14 for pi for simplicity
  }
  
  void toString() {
    System.out.println("Circle " + name + ". Area" + area(radius));
  }
    
  // method to allow for easy radius grab
  int getRadius() {
    return radius;
  }
}

// nodes for BST
class shapeNode {
  public Shape data;
  public shapeNode left;
  public shapeNode right;
  
  // creates a leaf
  public shapeNode(Shape data) {
    this(data, null, null);  
  }

  // creates a branch with data & links
  public shapeNode(Shape data, shapeNode left, shapeNode right) {
    this.data = data;
    this.left = left;
    this.right = right;
  }
}

public class Main {
  public static void main() {
    // creating the shapes
    Rectangle r1 = new Rectangle("r1", 6, 2);
    Rectangle r2 = new Rectangle("r2", 3, 5);
    Rectangle r3 = new Rectangle("r3", 2, 4);
    Rectangle r4 = new Rectangle("r4", 5, 3); // this will be used to make sure same areas cannot be added to BST
    Rectangle r5 = new Rectangle("r5", 7, 2);
    Rectangle r6 = new Rectangle("r6, 8, 5");
    Rectangle r7 = new Rectangle("r7", 3, 2);
    Rectangle r8 = new Rectangle("r8", 2, 1);
    
    // key node
    shapeNode n1 = new ShapeNode(r1);

    // building the tree
    
  }

}
