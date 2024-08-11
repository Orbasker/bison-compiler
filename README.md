# Setlang Compiler

The Setlang Compiler is a custom language compiler created by me, **Or Basker**, as part of a school project in compilation. This language allows for operations on sets and collections, including union, intersection, and more. The language provides syntax for variable declarations, control structures, and input/output operations, making it versatile for various computational tasks.

## Table of Contents

- [Getting Started](#getting-started)
- [Dependencies](#dependencies)
- [Compiling the Code](#compiling-the-code)
- [Writing New Code](#writing-new-code)
- [Examples](#examples)
- [Running the Examples](#running-the-examples)

## Getting Started

To get started with this project, you'll need to have the necessary tools installed and follow the instructions to compile and run the code.

### Dependencies

Ensure you have the following installed:

- **Flex**: A tool for generating scanners (lexical analyzers).
- **Bison**: A parser generator compatible with Yacc.
- **GCC/G++**: GNU Compiler Collection for compiling C/C++ code.

### Compiling the Code

The project includes a `Makefile` that automates the compilation process.


1. **Compile the custom language parser and lexer**:
    ```sh
    make
    ```

   This command will generate the `setlang` executable by compiling the Bison and Flex outputs along with the C++ source files.

2. **Run the parser** on an example file (e.g., `example1.set` or `example2.set`):
    ```sh
    make example1
    # or
    make example2
    ```

   These commands will run the `setlang` executable on the chosen example file, generate the corresponding `output.cpp` file, and then compile and execute it automatically.

3. **Run the parser on a custom file**:
    ```sh
    make run FILE=yourfile.set
    make compile_and_run
    ```

   Replace `yourfile.set` with the name of your custom input file. This will generate `output.cpp`, compile it, and run the resulting executable.

### Writing New Code

To write new code in this custom language, follow the syntax rules defined in the `lang.y` and `lang.l` files. Below is a quick overview:

- **Declarations**: Declare variables using `int`, `str`, `set`, or `collection`.
- **Expressions**: Perform arithmetic operations and set operations like union and intersection.
- **Control Structures**: Use `if`, `else`, `while`, and `for` loops.
- **Input/Output**: Use `input` and `output` commands to interact with the user.

## Examples

In this project, we have two detailed examples provided as part of the assignment. You can find these examples in the `example1.set` and `example2.set` files. These examples demonstrate how to work with collections, sets, and various operations such as union, intersection, and conditional logic in our custom language.

### Running the Examples

To run the provided examples, you can use the following `make` commands:

1. **Run the first example** (`example1.set`):
    ```sh
    make example1
    ```

   This command will compile and run the first example, generating the corresponding `output.cpp` file and executing it.

2. **Run the second example** (`example2.set`):
    ```sh
    make example2
    ```

   This command will compile and run the second example, generating the corresponding `output.cpp` file and executing it.

3. **Run a custom file**:
    ```sh
    make run FILE=yourfile.set
    make compile_and_run
    ```

   Replace `yourfile.set` with the name of your custom input file. This will generate, compile, and execute the C++ code based on the provided file.

### Short Examples

Here are some short examples to illustrate various features of the Setlang language:

1. **Simple Collection Declaration**:
   ```cpp
   collection students;
   students = {"Rafi_Suisa", "Tamar_Even", "Avi_Maoz"};
   output "Students in class:", students;
   ```

2. **Adding to a Collection**:
   ```cpp
   collection highTech;
   highTech = {"Apple", "Google"};
   highTech = highTech + {"Microsoft", "Nvidia"};
   output "High-tech companies:", highTech;
   ```

3. **Basic Set Operations**:
   ```cpp
   set grades, gradesHigh;
   grades = {85, 90, 78};
   gradesHigh = {90, 95, 88};
   output "All grades:", grades;
   output "High grades:", gradesHigh;
   output "Combined grades:", grades + gradesHigh;
   ```

4. **Intersection of Sets**:
   ```cpp
   set hardware, software;
   hardware = {"Apple", "Nvidia", "Sony"};
   software = {"Apple", "Microsoft", "Google"};
   output "Companies doing both hardware and software:", hardware & software;
   ```

5. **Conditional Output Based on Collection**:
   ```cpp
   collection highTech, software;
   highTech = {"Apple", "Google", "Microsoft"};
   software = {"Apple", "Microsoft"};

   if (highTech & software == software)
       output "All software companies are high-tech:", software;
   else
       output "Not all software companies are high-tech.";
   ```

6. **Adding Elements Conditionally**:
   ```cpp
   collection highGradeStudents;
   int grade;
   input "Enter grade:", grade;

   if (grade >= 90)
   {
       highGradeStudents = highGradeStudents + "Student_Name";
   }
   output "High-grade students:", highGradeStudents;
   ```

7. **Removing Elements from a Set**:
   ```cpp
   set hardware, gaming;
   hardware = {"Sony", "Apple", "Google"};
   gaming = {"Sony", "Nintendo"};

   output "Hardware but not gaming companies:", hardware - gaming;
   ```

8. **Loop Through a Collection**:
   ```cpp
   collection students;
   students = {"Rafi_Suisa", "Tamar_Even", "Avi_Maoz"};

   for (student : students)
       output "Student name:", student;
   ```

9. **Counting Elements in a Set**:
   ```cpp
   set grades;
   grades = {85, 90, 78, 92};

   output "Number of grades:", |grades|;
   ```

10. **Collection Union**:
    ```cpp
    collection software, hardware;
    software = {"Microsoft", "Google"};
    hardware = {"Sony", "Apple"};

    output "Companies in either software or hardware:", software + hardware;
    ```

