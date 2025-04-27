#include "quiz.h"
#include "ui_quiz.h"
#include <QMessageBox>
#include <random>
#include <QProgressBar>
#include <QTimer>
#include "databasemanager.h"


// Global question bank
std::vector<Question> questionBank = {

// Programming Languages - Easy
    {"What is the extension for C++ files?", {"cpp", "py", "java", "txt"}, 0, "Programming Languages", "Easy"},
    {"What does HTML stand for?", {"Hyper Text Markup Language", "Hyper Tool Markup Language", "Hyperlink Markup Language", "Hyper Text Machine Language"}, 0, "Programming Languages", "Easy"},
    {"Which language is primarily used for Android app development?", {"Java", "Python", "C#", "Ruby"}, 0, "Programming Languages", "Easy"},
    {"What is the symbol for single-line comments in Python?", {"#", "//", "/*", "<!--"}, 0, "Programming Languages", "Easy"},
    {"Which of these is a markup language?", {"HTML", "C", "Python", "Java"}, 0, "Programming Languages", "Easy"},
    {"Which keyword is used to declare a variable in Java?", {"var", "let", "int", "declare"}, 0, "Programming Languages", "Easy"},
    {"What is the default value of an uninitialized int in C++?", {"0", "undefined", "null", "garbage value"}, 0, "Programming Languages", "Easy"},
    {"Which programming language is used for web development alongside HTML and CSS?", {"JavaScript", "Python", "Java", "C++"}, 0, "Programming Languages", "Easy"},
    {"What is the output operator "
     "C++?", {"<<", ">>", "==", "="}, 0, "Programming Languages", "Easy"},
    {"Which language is primarily used for statistical analysis?", {"R", "C", "Python", "Java"}, 0, "Programming Languages", "Easy"},
    {"What is the file extension for Python scripts?", {".py", ".java", ".c", ".cpp"}, 0, "Programming Languages", "Easy"},
    {"Which programming paradigm focuses on objects?", {"Object-Oriented", "Functional", "Procedural", "Declarative"}, 0, "Programming Languages", "Easy"},
    {"What does IDE stand for?", {"Integrated Development Environment", "Interactive Debugging Environment", "Integrated Design Editor", "Intelligent Development Engine"}, 0, "Programming Languages", "Easy"},
    {"Which of these is a database query language?", {"SQL", "C", "Python", "PHP"}, 0, "Programming Languages", "Easy"},
    {"What does CSS stand for?", {"Cascading Style Sheets", "Cascading Simple Styles", "Creative Style Sheets", "None of the above"}, 0, "Programming Languages", "Easy"},
    {"What is the output of 5+3 in Python?", {"8", "53", "Error", "None"}, 0, "Programming Languages", "Easy"},
    {"Which keyword is used to define a function in Python?", {"def", "function", "lambda", "method"}, 0, "Programming Languages", "Easy"},
    {"Which language is best suited for system-level programming?", {"C", "HTML", "JavaScript", "Python"}, 0, "Programming Languages", "Easy"},
    {"What does JVM stand for?", {"Java Virtual Machine", "Java Vendor Model", "Java Version Manager", "None of the above"}, 0, "Programming Languages", "Easy"},
    {"Which programming language is used for iOS app development?", {"Swift", "Python", "Java", "C++"}, 0, "Programming Languages", "Easy"},

    // Programming Languages - Medium
    {"Which of the following is an object-oriented programming language?", {"C", "C++", "Assembly", "Fortran"}, 1, "Programming Languages", "Medium"},
    {"What is the keyword used to define a class in Java?", {"class", "def", "object", "function"}, 0, "Programming Languages", "Medium"},
    {"Which function is used to print output in C++?", {"cout", "print", "echo", "output"}, 0, "Programming Languages", "Medium"},
    {"What is Python primarily known for?", {"Data Science", "Web Development", "Machine Learning", "All of the above"}, 3, "Programming Languages", "Medium"},
    {"What is the default return type of the main function in C++?", {"int", "void", "float", "char"}, 0, "Programming Languages", "Medium"},
    {"Which of these is not a programming language?", {"HTML", "Python", "C++", "Java"}, 0, "Programming Languages", "Medium"},
    {"What does the static keyword do in Java?", {"Makes a variable shared", "Creates an instance", "Restricts access", "None of the above"}, 0, "Programming Languages", "Medium"},
    {"What is the purpose of the virtual keyword in C++?", {"Enable polymorphism", "Create templates", "Manage memory", "None of the above"}, 0, "Programming Languages", "Medium"},
    {"Which language supports the try-catch mechanism for error handling?", {"C++", "Python", "Java", "All of the above"}, 3, "Programming Languages", "Medium"},
    {"What is the output of printf(\"%d\", 7 & 3) in C?", {"3", "7", "5", "1"}, 0, "Programming Languages", "Medium"},
    {"What does the return keyword do in a function?", {"Exits the function and returns a value", "Creates a loop", "Terminates the program", "Defines a variable"}, 0, "Programming Languages", "Medium"},
    {"What is the purpose of the include directive in C++?", {"Include libraries", "Define macros", "Create classes", "Write comments"}, 0, "Programming Languages", "Medium"},
    {"Which of these is a high-level programming language?", {"Assembly", "Python", "Machine Code", "Binary"}, 1, "Programming Languages", "Medium"},
    {"What is the difference between == and = in C++?", {"Comparison vs Assignment", "Addition vs Subtraction", "Multiplication vs Division", "None of the above"}, 0, "Programming Languages", "Medium"},
    {"Which function is used to allocate memory dynamically in C?", {"malloc", "alloc", "memalloc", "new"}, 0, "Programming Languages", "Medium"},
    {"What does API stand for?", {"Application Programming Interface", "Advanced Programming Instruction", "Application Programming Integration", "None of the above"}, 0, "Programming Languages", "Medium"},
    {"What is the use of the break keyword in loops?", {"Exits the loop", "Starts a new iteration", "Skips a step", "None of the above"}, 0, "Programming Languages", "Medium"},
    {"Which of these supports operator overloading?", {"C++", "Python", "Java", "C"}, 0, "Programming Languages", "Medium"},
    {"What does the continue statement do in a loop?", {"Skips to the next iteration", "Exits the loop", "Terminates the program", "None of the above"}, 0, "Programming Languages", "Medium"},
    {"Which of these is a mutable data type in Python?", {"List", "Tuple", "String", "All of the above"}, 0, "Programming Languages", "Medium"},

    // Programming Languages - Hard
    {"What is the result of the following code in Python: [x**2 for x in range(5)]?", {"[0, 1, 4, 9, 16]", "[0, 1, 2, 3, 4]", "[1, 4, 9, 16, 25]", "[1, 2, 3, 4, 5]"}, 0, "Programming Languages", "Hard"},
    {"Which of these languages supports multi-threading directly?", {"Java", "C", "Python", "PHP"}, 0, "Programming Languages", "Hard"},
    {"What is the size of an int in C++ on a 64-bit system?", {"4 bytes", "2 bytes", "8 bytes", "16 bytes"}, 0, "Programming Languages", "Hard"},
    {"What is the time complexity of accessing an element in an array by index?", {"O(1)", "O(n)", "O(log n)", "O(n^2)"}, 0, "Programming Languages", "Hard"},
    {"What is the primary use of the volatile keyword in C++?", {"Prevent optimization", "Define constants", "Enable threading", "Disable compiler warnings"}, 0, "Programming Languages", "Hard"},
    {"Which C++ feature allows a function to have multiple definitions with different parameters?", {"Function Overloading", "Function Overriding", "Polymorphism", "Encapsulation"}, 0, "Programming Languages", "Hard"},
    {"What is the difference between public, protected, and private in C++?", {"Access control", "Memory management", "Error handling", "None of the above"}, 0, "Programming Languages", "Hard"},
    {"What is the purpose of the friend keyword in C++?", {"Access private members", "Optimize memory", "Handle exceptions", "None of the above"}, 0, "Programming Languages", "Hard"},
    {"What is a lambda function in Python?", {"Anonymous function", "Named function", "Error handling mechanism", "None of the above"}, 0, "Programming Languages", "Hard"},
    {"What does the auto keyword do in modern C++?", {"Automatically deduce type", "Create an instance", "Optimize memory", "None of the above"}, 0, "Programming Languages", "Hard"},
    {"What is a template in C++?", {"Generic programming feature", "Error handling mechanism", "Data type conversion", "None of the above"}, 0, "Programming Languages", "Hard"},
    {"What is the purpose of the final keyword in Java?", {"Prevent inheritance", "Create constants", "Both A and B", "None of the above"}, 2, "Programming Languages", "Hard"},
    {"What does the pass keyword do in Python?", {"Does nothing", "Ends a loop", "Returns a value", "Creates a variable"}, 0, "Programming Languages", "Hard"},
    {"What is a singleton pattern?", {"Ensures only one instance of a class", "Allows multiple instances", "Optimizes memory", "Handles exceptions"}, 0, "Programming Languages", "Hard"},
    {"Which C++ feature is used to achieve runtime polymorphism?", {"Virtual functions", "Templates", "Overloading", "Macros"}, 0, "Programming Languages", "Hard"},
    {"What is the purpose of a constructor in OOP?", {"Initialize an object", "Delete an object", "Handle errors", "None of the above"}, 0, "Programming Languages", "Hard"},
    {"What is the difference between deep copy and shallow copy?", {"Copy by value vs reference", "Compile-time vs runtime", "Static vs dynamic", "None of the above"}, 0, "Programming Languages", "Hard"},
    {"Which of the following is a functional programming feature in Python?", {"Map and reduce", "For loop", "Static typing", "None of the above"}, 0, "Programming Languages", "Hard"},
    {"What is the diamond problem in C++?", {"Ambiguity in multiple inheritance", "Memory allocation issue", "Error in templates", "None of the above"}, 0, "Programming Languages", "Hard"},
    {"What is the output of the following Python code? print(5//2)", {"2", "2.5", "3", "Error"}, 0, "Programming Languages", "Hard"},


    // Object-Oriented Programming (OOP) - Easy
    {"What does OOP stand for?", {"Object-Oriented Programming", "Object-Oriented Principles", "Operational Object Programs", "Only Object Paradigms"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"Which concept binds code and data together?", {"Encapsulation", "Inheritance", "Polymorphism", "Abstraction"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"What is the default access specifier for class members in C++?", {"Private", "Public", "Protected", "Default"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"Which keyword is used to define a class in C++?", {"class", "struct", "define", "object"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"Which Object-Oriented Programming (OOP) concept allows the use of the same function name for different purposes?", {"Polymorphism", "Inheritance", "Abstraction", "Encapsulation"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"What is a constructor in Object-Oriented Programming (OOP)?", {"Special method to initialize objects", "A destructor", "A method to destroy objects", "None of the above"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"Which keyword represents an object calling its own member functions?", {"this", "self", "object", "class"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"Which of these is an example of inheritance?", {"A child class inheriting parent class properties", "Defining a function", "Encapsulation of data", "None of the above"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"What is the role of a destructor?", {"Free resources when an object is destroyed", "Initialize an object", "Perform operations", "None of the above"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"Which of the following is not a principle of Object-Oriented Programming (OOP)?", {"Compilation", "Encapsulation", "Polymorphism", "Abstraction"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"What does dynamic polymorphism use?", {"Virtual functions", "Overloading", "Templates", "Constructors"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"Which access specifier allows visibility only within the class?", {"Private", "Public", "Protected", "Default"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"Which function allows different objects to be treated as the same?", {"Virtual function", "Static function", "Template function", "None of the above"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"Which Object-Oriented Programming (OOP) concept hides implementation details?", {"Abstraction", "Encapsulation", "Inheritance", "Polymorphism"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"What is the purpose of the friend keyword?", {"Grant access to private members", "Declare a friend class", "Override a function", "None of the above"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"Which keyword is used to prevent inheritance?", {"final", "virtual", "override", "static"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"What does the protected keyword do?", {"Access in derived classes", "Access only within the class", "Access globally", "None"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"What is operator overloading?", {"Defining new meaning for operators", "Defining multiple operators", "Using operators on objects", "None"}, 0, "Object-Oriented Programming (OOP)", "Easy"},
    {"Which of these is not a type of inheritance?", {"Multiple", "Hierarchical", "Overloaded", "Multilevel"}, 2, "Object-Oriented Programming (OOP)", "Easy"},
    {"Which function is called automatically during object destruction?", {"Destructor", "Constructor", "Virtual function", "Static function"}, 0, "Object-Oriented Programming (OOP)", "Easy"},

    // Object-Oriented Programming (OOP) - Medium
    {"What is the purpose of virtual functions?", {"Enable runtime polymorphism", "Static binding", "Memory allocation", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What is multiple inheritance?", {"Class inheriting from multiple base classes", "Inheritance of all members", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"Which keyword resolves ambiguity in multiple inheritance?", {"Scope resolution operator (::)", "virtual", "override", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What is an abstract class?", {"Class with pure virtual functions", "Class with all functions", "Encapsulated class", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"Which keyword is used for an interface in Java?", {"interface", "abstract", "class", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"How is operator overloading implemented in C++?", {"Member functions", "Template functions", "Friend functions", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What does the virtual keyword signify?", {"Overridable function", "Static binding", "Private function", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What is the role of pure virtual functions?", {"Define interface for derived classes", "Static behavior", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What is dynamic dispatch?", {"Method overriding at runtime", "Static function binding", "Object creation", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What happens when a base class pointer points to a derived class object?", {"Runtime polymorphism", "Compilation error", "Ambiguity", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"Which is not a valid way to implement polymorphism?", {"Using macros", "Using virtual functions", "Operator overloading", "Templates"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What is the diamond problem?", {"Ambiguity in multiple inheritance", "Overloading error", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What does the override keyword in C++ signify?", {"Explicit overriding", "Operator overload", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"Which keyword ensures resource safety in C++?", {"RAII (Resource Acquisition Is Initialization)", "Dynamic binding", "Templates", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What does the term 'early binding' mean?", {"Compile-time linking", "Runtime polymorphism", "Object destruction", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What is a mixin class?", {"Provides reusable functionality", "Base class", "Static class", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"Which type of inheritance creates ambiguity?", {"Multiple inheritance", "Single inheritance", "Hierarchical inheritance", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What does the keyword delete do in C++?", {"Deallocates memory", "Deletes variables", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What is slicing in Object-Oriented Programming (OOP)?", {"Derived object assigned to base type", "String slicing", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},
    {"What happens when a virtual destructor is not defined?", {"Undefined behavior", "Compiler warning", "None"}, 0, "Object-Oriented Programming (OOP)", "Medium"},

    // Object-Oriented Programming (OOP) - Hard
    {"What is a virtual destructor used for?", {"To ensure proper destruction of derived class objects", "To allocate memory", "To define interface classes", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What is the purpose of a pure virtual destructor?", {"To enforce derived class implementation", "To prevent object instantiation", "To release resources in base class", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What does the term polymorphic base class mean?", {"Class designed for inheritance with virtual functions", "Base class that uses templates", "Class that does not support polymorphism", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"How is the 'CRTP' pattern implemented in C++?", {"Derived class uses base class as a template parameter", "Base class uses derived class as a template parameter", "No templates involved", "None"}, 1, "Object-Oriented Programming (OOP)", "Hard"},
    {"What happens if you override a base class method without the override specifier?", {"The method may not override correctly", "The code will not compile", "The base class method will be deleted", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What is object slicing?", {"Truncation of derived class data when assigned to base class", "Memory allocation failure", "Static method conflict", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What does the 'Bridge' design pattern achieve?", {"Separates abstraction from implementation", "Encapsulates object creation", "Manages object destruction", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What is the difference between covariance and contravariance?", {"Covariance allows return type narrowing; contravariance allows parameter widening", "Covariance allows parameter narrowing; contravariance allows return type widening", "Both refer to runtime polymorphism", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What does the 'Visitor' pattern do?", {"Separates algorithm from the object it operates on", "Manages multiple inheritance conflicts", "Ensures memory safety", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"How is dynamic dispatch implemented?", {"Using vtable and vptr", "Through static binding", "Using template specialization", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What is the effect of marking a class as final in C++?", {"Prevents further inheritance", "Enforces single inheritance", "Prevents operator overloading", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What happens if a pure virtual function is called within a constructor?", {"Undefined behavior", "Runtime error", "Compiler warning", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What does the acronym 'RAII' stand for in C++?", {"Resource Acquisition Is Initialization", "Runtime Application Interface Interfacing", "Resource Allocation in Inheritance", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What is the Liskov Substitution Principle (LSP)?", {"Derived classes must be substitutable for their base classes", "Base classes must inherit properties of derived classes", "Both classes must use templates", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"How does dependency inversion principle help?", {"By decoupling high-level and low-level modules", "By forcing use of templates", "By ensuring inheritance chains are deep", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What is the primary use of the 'Prototype' pattern?", {"Cloning objects efficiently", "Managing interface segregation", "Preventing multiple inheritance", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What is the key difference between shallow and deep copy?", {"Deep copy duplicates all objects, shallow copy copies references", "Shallow copy is faster than deep copy", "Both are the same", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What is the 'Factory Method' pattern used for?", {"To create objects without specifying their concrete type", "To encapsulate object destruction", "To enforce single responsibility principle", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What does 'Encapsulation' primarily aim to achieve?", {"Hiding internal state and requiring controlled access", "Defining interface classes", "Preventing polymorphism", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},
    {"What happens if a destructor is not virtual in a polymorphic base class?", {"Derived class destructors won't be called", "Memory leak will occur", "Base class constructors will fail", "None"}, 0, "Object-Oriented Programming (OOP)", "Hard"},

    // Data Structures & Algorithms (DSA) - Easy
    {"What is the time complexity of accessing an element in an array by index?", {"O(1)", "O(n)", "O(log n)", "O(n^2)"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"Which of these is a linear data structure?", {"Array", "Tree", "Graph", "Hash Map"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"What is the purpose of a stack?", {"Last In First Out (LIFO)", "First In First Out (FIFO)", "Data storage", "None of the above"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"Which sorting algorithm has the best average case performance?", {"Merge Sort", "Bubble Sort", "Insertion Sort", "Selection Sort"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"What is the primary purpose of a queue?", {"FIFO", "LIFO", "Sorting", "Searching"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"What is the output of a breadth-first search?", {"Level order traversal", "In-order traversal", "Post-order traversal", "Pre-order traversal"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"What is the space complexity of a linked list?", {"O(n)", "O(1)", "O(log n)", "O(n^2)"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"Which of these is not a searching algorithm?", {"Binary Search", "Linear Search", "Quick Sort", "Hashing"}, 2, "Data Structures & Algorithms (DSA)", "Easy"},
    {"What is the function of a hash table?", {"Map keys to values", "Store integers", "Sort elements", "Search elements"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"Which data structure uses a priority queue?", {"Dijkstra's Algorithm", "Merge Sort", "Quick Sort", "DFS"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"Which of these is a non-linear data structure?", {"Tree", "Array", "Stack", "Queue"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"What does DFS stand for?", {"Depth First Search", "Data Flow Search", "Dynamic Function Sorting", "Depth Flow System"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"What is the worst-case time complexity of bubble sort?", {"O(n^2)", "O(n)", "O(log n)", "O(1)"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"Which of the following is a dynamic data structure?", {"Linked List", "Array", "Hash Map", "None of the above"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"What is a binary tree?", {"Tree with at most 2 children", "Tree with at most 3 children", "Tree with no children", "None of the above"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"Which of the following is a greedy algorithm?", {"Kruskal's Algorithm", "Merge Sort", "Dynamic Programming", "DFS"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"What is a circular queue?", {"Queue with connected ends", "Queue with multiple exits", "FIFO with priority", "None of the above"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"What is the maximum degree of a node in a binary tree?", {"2", "1", "3", "4"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"What does the 'front' of a queue refer to?", {"First element", "Middle element", "Last element", "None of the above"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},
    {"What does LIFO stand for?", {"Last In First Out", "Last In First On", "Least Important First Out", "None of the above"}, 0, "Data Structures & Algorithms (DSA)", "Easy"},

    // Data Structures & Algorithms (DSA) - Medium
    {"Which of the following is a self-balancing binary search tree?", {"AVL Tree", "Binary Heap", "B-Tree", "Red-Black Tree"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"What is the time complexity of binary search?", {"O(log n)", "O(n)", "O(n^2)", "O(1)"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"What is the purpose of hashing?", {"Efficient data retrieval", "Data compression", "Data sorting", "None of the above"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"Which data structure is used in a breadth-first search?", {"Queue", "Stack", "Hash Map", "Heap"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"What is the height of a binary tree with n nodes?", {"log(n)", "n", "n/2", "n^2"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"Which algorithm is used for shortest path?", {"Dijkstra's", "DFS", "Merge Sort", "Binary Search"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"What is the complexity of quicksort in the average case?", {"O(n log n)", "O(n^2)", "O(log n)", "O(1)"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"What does a min-heap guarantee?", {"Smallest element at root", "Largest element at root", "Sorted data", "All elements equal"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"Which of these is used to detect a cycle in a graph?", {"Union-Find", "Binary Search", "Stack", "Queue"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"What is the time complexity of inserting into a heap?", {"O(log n)", "O(n)", "O(1)", "O(n^2)"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"Which is not a type of tree traversal?", {"Reverse", "In-order", "Pre-order", "Post-order"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"Which algorithm uses a divide-and-conquer strategy?", {"Merge Sort", "Bubble Sort", "DFS", "BFS"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"What is the advantage of linked lists over arrays?", {"Dynamic size", "Faster access", "Better sorting", "None"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"What does Kruskal's algorithm find?", {"Minimum Spanning Tree", "Shortest Path", "Longest Path", "Cycle"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"What is the purpose of a graph adjacency matrix?", {"Represent edges", "Store weights", "Both A and B", "None"}, 2, "Data Structures & Algorithms (DSA)", "Medium"},
    {"What is a Trie?", {"Prefix tree", "Binary tree", "Heap", "Graph"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"What is a sentinel node in a linked list?", {"Dummy node", "Root node", "Middle node", "Last node"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"Which of these is used to find strongly connected components?", {"Kosaraju's Algorithm", "Prim's Algorithm", "DFS", "BFS"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"Which sorting algorithm uses a binary heap?", {"Heap Sort", "Quick Sort", "Merge Sort", "Selection Sort"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},
    {"Which algorithm solves the all-pairs shortest path problem?", {"Floyd-Warshall", "Kruskal's", "Dijkstra's", "Bellman-Ford"}, 0, "Data Structures & Algorithms (DSA)", "Medium"},

    // Data Structures & Algorithms (DSA) - Hard
    {"What is the complexity of Floyd-Warshall?", {"O(n^3)", "O(n log n)", "O(n^2)", "O(log n)"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"Which tree is used for indexing in databases?", {"B-Tree", "AVL Tree", "Red-Black Tree", "Binary Search Tree"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is the time complexity of inserting into a red-black tree?", {"O(log n)", "O(n)", "O(1)", "O(n^2)"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What does Tarjan's algorithm compute?", {"Strongly Connected Components", "Shortest Path", "Minimum Spanning Tree", "Longest Path"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is the amortized time complexity of inserting into a dynamic array?", {"O(1)", "O(n)", "O(log n)", "O(n^2)"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is a Fibonacci heap used for?", {"Decrease-Key Operation", "Sorting", "Balancing Trees", "None"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is the difference between Prim's and Kruskal's algorithms?", {"Edge vs Node selection", "Directed vs Undirected", "Greedy vs Dynamic", "None"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is the diameter of a tree?", {"Longest path between nodes", "Number of nodes", "Height", "None"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"Which algorithm is used for maximum flow problems?", {"Ford-Fulkerson", "Dijkstra's", "Kruskal's", "Bellman-Ford"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is a splay tree?", {"Self-adjusting BST", "Heap", "Graph", "None"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is the purpose of a skip list?", {"Efficient search", "Sorting", "Dynamic sizing", "None"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"Which algorithm is used for topological sorting?", {"DFS", "BFS", "Union-Find", "Dijkstra's"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is the complexity of Timsort?", {"O(n log n)", "O(n)", "O(log n)", "O(n^2)"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"Which graph traversal algorithm is recursive?", {"DFS", "BFS", "Dijkstra's", "Kruskal's"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is the purpose of a Bloom filter?", {"Test set membership", "Sort data", "Hashing", "Graph traversal"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is a top-down approach to dynamic programming?", {"Memoization", "Tabulation", "Divide and Conquer", "None"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is the running time of a merge sort in the worst case?", {"O(n log n)", "O(n^2)", "O(n)", "O(log n)"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is the purpose of the Bellman-Ford algorithm?", {"Finding shortest paths in graphs with negative weights", "Finding the longest path in a DAG", "Detecting cycles in graphs", "Balancing trees"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is a treap?", {"A binary tree with heap properties", "A self-balancing binary search tree", "A special type of graph", "None"}, 0, "Data Structures & Algorithms (DSA)", "Hard"},
    {"What is the complexity of constructing a suffix array?", {"O(n log n)", "O(n^2)", "O(n)", "O(log n)"}, 0, "Data Structures & Algorithms (DSA)", "Hard"}
};

int
    correctAnswers = 0;

quiz::quiz(QWidget *parent, const QString& category, const QString& level, int userId)
    : QDialog(parent)                // Base class initialization
    , ui(new Ui::quiz)               // Initialize in order of declaration
    , questions()                    // Default initialize the vector
    , currentQuestionIndex(0)        // Initialize current question index
    , score(0)                       // Initialize score
    , elapsedTime(0)                 // Initialize elapsed time
    , category(category)             // Initialize category
    , level(level)                   // Initialize level
    , currentUserId(userId)          // Initialize currentUserId with the provided userId
    , progressBar(nullptr)           // Ensure progressBar starts as null
    , timer(nullptr)                 // Ensure timer starts as null

{
    ui->setupUi(this);
    ui->lcdScore->display(0); // Initialize the QLCDNumber to 0
    loadQuiz(category, level);  // Load questions based on category and level

    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);  // Set the range (0-100% for 100 seconds)
    progressBar->setValue(0);  // Initial value
    progressBar->setGeometry(50, 50, 300, 30);  // Set position and size

    timer = new QTimer(this);
    // Connect the timeout signal of the timer to the onTimeUp slot
    connect(timer, &QTimer::timeout, this, &quiz::updateProgress);  // This triggers the onTimeUp slot when time runs out

    timer->start(1000);  // Update progress every 1000 ms (1 second)

    // Enable word wrapping for the facts label
    ui->questionLabel->setWordWrap(true);
}


quiz::~quiz()
{
    delete ui;
}


bool quiz::quizCompleted = false;

void quiz::onTimeUp()
{
    // If the quiz is already completed, do nothing.
    if (quizCompleted) {
        return;
    }

    // Assuming you want to show the message when the time runs out
    if (!this->isVisible()) {
        return;  // Exit early if the dialog is not visible
    }

    // Calculate the final score based on correct answers and level
    int finalScore = correctAnswers * getScoreForLevel();  // Final score calculation

    // Create a custom message box
    QMessageBox messageBox(this);
    messageBox.setWindowTitle("Time's Up!");  // Set the window title
    messageBox.setText("Your time is up! Final score: " + QString::number(finalScore));  // Set the message text

    // Set the custom stylesheet for the message box
    messageBox.setStyleSheet("QMessageBox {"
                             "background-color: #f0f0f0;"  // Light background
                             "color: #333333; }"           // Dark text color
                             "QPushButton {"
                             "background-color: #4CAF50;"  // Button background color (green)
                             "color: #ffffff; }");         // Button text color (white)

    // Show the custom message box
    messageBox.exec();

    // Stop the timer
    timer->stop();

    // Display final score in the QLCDNumber widget
    ui->lcdScore->display(finalScore);  // Display the final score

    // Save the score to the leaderboard after the time is up
    saveScoreToLeaderboard(currentUserId, finalScore);  // Save score to leaderboard

    accept();  // Close the dialog after time is up
}


void quiz::updateProgress()
{
    elapsedTime += 1;  // Increment elapsed time by 1 second
    int progress = (elapsedTime / 100.0) * 100;  // Calculate progress percentage

    progressBar->setValue(progress);  // Update progress bar value

    if (elapsedTime >= 100) {  // Stop the timer when it reaches 100 seconds
        timer->stop();  // Stop the timer after 100 seconds
        onTimeUp();  // Trigger onTimeUp() when the time is up
    }
}


void quiz::loadQuiz(const QString& category, const QString& level)
{
    questions = getQuestionsForCategoryAndLevel(category, level); // Get filtered questions

    // Shuffle the questions and select the first 10 questions (or fewer if there are not enough)
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions.begin(), questions.end(), g);  // Randomly shuffle the questions

    if (questions.size() > 10) {
        questions.resize(10);  // Keep only the first 10 questions
    }

    // Now shuffle the options of each question
    for (auto& question : questions) {
        shuffleOptions(question);  // Shuffle options for each question and update the correct answer index
    }

    currentQuestionIndex = 0;  // Reset question index
    correctAnswers = 0;         // Reset the correct answers count
    ui->lcdScore->display(0);   // Reset the LCD score display to 0
    displayQuestion();          // Display the first question

}

void quiz::displayQuestion()
{
    // Uncheck all radio buttons before displaying the next question
    ui->radioButton1->setChecked(false);
    ui->radioButton2->setChecked(false);
    ui->radioButton3->setChecked(false);
    ui->radioButton4->setChecked(false);

    // Ensure that the radio buttons are really unchecked
    ui->radioButton1->setAutoExclusive(false);
    ui->radioButton2->setAutoExclusive(false);
    ui->radioButton3->setAutoExclusive(false);
    ui->radioButton4->setAutoExclusive(false);

    // Now uncheck them again
    ui->radioButton1->setChecked(false);
    ui->radioButton2->setChecked(false);
    ui->radioButton3->setChecked(false);
    ui->radioButton4->setChecked(false);

    // After resetting the radio buttons, ensure they go back to exclusive mode.
    ui->radioButton1->setAutoExclusive(true);
    ui->radioButton2->setAutoExclusive(true);
    ui->radioButton3->setAutoExclusive(true);
    ui->radioButton4->setAutoExclusive(true);

    if (currentQuestionIndex >= static_cast<int>(questions.size())) {
        // End of quiz, show the score
        QMessageBox::information(this, "Quiz Completed", "Your score: " + QString::number(score));
        return;
    }

    // Remove const to modify the question's correctAnswer
    Question& currentQuestion = questions[currentQuestionIndex]; // Make it non-const

    // Convert the options array to a std::vector
    std::vector<QString> shuffledOptions(currentQuestion.options, currentQuestion.options + 4);

    // Shuffle the options to avoid always starting from index 0
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffledOptions.begin(), shuffledOptions.end(), g);

    // Display the question and shuffled options
    ui->questionLabel->setText(currentQuestion.question);
    ui->radioButton1->setText(shuffledOptions[0]);
    ui->radioButton2->setText(shuffledOptions[1]);
    ui->radioButton3->setText(shuffledOptions[2]);
    ui->radioButton4->setText(shuffledOptions[3]);

    // Update the correct answer index based on shuffled options
    currentQuestion.correctAnswer = std::distance(shuffledOptions.begin(), std::find(shuffledOptions.begin(), shuffledOptions.end(), currentQuestion.options[currentQuestion.correctAnswer]));
}



int quiz::getScoreForLevel()
{
    if (level == "Easy") {
        return 10;  // 10 points per correct answer on Easy level
    } else if (level == "Medium") {
        return 20;  // 20 points per correct answer on Medium level
    } else if (level == "Hard") {
        return 30;  // 30 points per correct answer on Hard level
    }
    return 1; // Default to 1 for any unrecognized level (shouldn't happen)
}


std::vector<Question> quiz::getQuestionsForCategoryAndLevel(const QString& category, const QString& level)
{
    std::vector<Question> filteredQuestions;

    // Filter questions based on category and level
    for (const auto& question : questionBank) {  // Access the global questionBank
        if (question.category == category && question.level == level) {
            filteredQuestions.push_back(question);
        }
    }

    // Shuffle the questions to ensure random selection
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(filteredQuestions.begin(), filteredQuestions.end(), g);

    // Return the first 10 questions for the quiz
    if (filteredQuestions.size() > 10) {
        filteredQuestions.resize(10);
    }
    return filteredQuestions;
}
// In quiz.cpp

void quiz::shuffleOptions(Question& question)
{
    // Copy options to a vector for shuffling
    std::vector<QString> options(question.options, question.options + 4);

    // Create a random number generator
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::shuffle(options.begin(), options.end(), engine);  // Shuffle the options

    // Find the correct answer in the shuffled list
    QString correctOption = question.options[question.correctAnswer];
    int newCorrectAnswerIndex = std::distance(options.begin(), std::find(options.begin(), options.end(), correctOption));

    // Update the question's options and correctAnswer index
    for (int i = 0; i < 4; ++i) {
        question.options[i] = options[i];
    }
    question.correctAnswer = newCorrectAnswerIndex;  // Update the correctAnswer index
}


void quiz::on_pushButton_2_clicked()
{
    // If the quiz is already completed, do nothing.
    if (quizCompleted) {
        return;
    }

    int selectedAnswer = -1;

    // Determine which radio button is selected
    if (ui->radioButton1->isChecked()) {
        selectedAnswer = 0;
    } else if (ui->radioButton2->isChecked()) {
        selectedAnswer = 1;
    } else if (ui->radioButton3->isChecked()) {
        selectedAnswer = 2;
    } else if (ui->radioButton4->isChecked()) {
        selectedAnswer = 3;
    }

    qDebug() << "Selected Answer:" << selectedAnswer;
    qDebug() << "Correct Answer:" << questions[currentQuestionIndex].correctAnswer;

    // Check if the answer is correct
    if (selectedAnswer == questions[currentQuestionIndex].correctAnswer) {
        correctAnswers++;  // Increment the correct answers counter
        ui->lcdScore->display(correctAnswers);  // Update QLCDNumber to show the correct answers count
    }

    currentQuestionIndex++;  // Move to the next question

    if (currentQuestionIndex >= static_cast<int>(questions.size())) {
        // End of quiz
        int finalScore = correctAnswers * getScoreForLevel();  // Final score based on level and correct answers

        // Save score to leaderboard
        saveScoreToLeaderboard(currentUserId, finalScore);  // Save the score in the leaderboard table

        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Quiz Completed");
        messageBox.setText("Your score: " + QString::number(finalScore));
        messageBox.setStyleSheet("QMessageBox {"
                                 "background-color: #f0f0f0;"  // Light background
                                 "color: #333333; }"           // Dark text color
                                 "QPushButton {"
                                 "background-color: #4CAF50;"  // Button background color (green)
                                 "color: #ffffff; }");         // Button text color (white)

        messageBox.exec();
        accept();
    } else {
        // Show the next question
        displayQuestion();
    }
}




void quiz::closeEvent(QCloseEvent* event)
{
    if (timer) {
        timer->stop();  // Stop the timer to prevent further timeout signals
    }
    QDialog::closeEvent(event);  // Call the base class implementation
}

void quiz::saveScoreToLeaderboard(int userId, int score) {
    // Use DatabaseManager to get the active database connection
    DatabaseManager dbManager;
    if (!dbManager.connectToDatabase()) {
        qDebug() << "Failed to connect to database.";
        return;
    }

    QSqlQuery query(DatabaseManager::getDatabase());

    // Check if user already exists in leaderboard
    query.prepare("SELECT COUNT(*) FROM leaderboard WHERE user_id = :user_id");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qDebug() << "Failed to check user existence:" << query.lastError().text();
        return;
    }

    query.next();
    int count = query.value(0).toInt();
    qDebug() << "User  exists count:" << count;

    if (count > 0) {
        // Prepare the query to fetch the current score of the user
        query.prepare("SELECT score FROM leaderboard WHERE user_id = :user_id");
        query.bindValue(":user_id", userId);

        // Execute the query to retrieve the current score
        if (query.exec() && query.next()) {
            // Get the current score from the query result
            int currentScore = query.value("score").toInt();

            // Add the new score to the current score
            int newScore = currentScore + score;

            // Now, prepare the query to update the leaderboard with the new score
            query.prepare("UPDATE leaderboard SET score = :score WHERE user_id = :user_id");
            query.bindValue(":score", newScore);  // New total score
            query.bindValue(":user_id", userId);  // User ID

            // Execute the query to update the score
            if (query.exec()) {
                qDebug() << "Score updated successfully. User ID:" << userId << "New Score:" << newScore;
            } else {
                // Error handling, e.g., log or display an error message
                qDebug() << "Failed to update score:" << query.lastError().text();
            }
        } else {
            // Error handling if the user was not found or there was an issue fetching the current score
            qDebug() << "Failed to fetch current score for User ID:" << userId << query.lastError().text();
        }

    } else {
        // User doesn't exist; insert a new record
        query.prepare("INSERT INTO leaderboard (user_id, score) VALUES (:user_id, :score)");
        query.bindValue(":user_id", userId);
        query.bindValue(":score", score);

        if (!query.exec()) {
            qDebug() << "Failed to save new score:" << query.lastError().text();
        } else {
            qDebug() << "New score saved successfully. User ID:" << userId << "Score:" << score;
        }
    }
}
