Prompt

This assignment presents code that creates an in-memory database and runs a number of queries with and without SQL injection, always dumping the results to the console. You need to modify the run_query() function to detect a potential SQL injection attack, prevent it, and display that information to the console. The specific type of SQL injection attack is the “OR value=value;” attack, and you must defend against that specific attack with value being any allowed SQL literal (numeric or quoted string).

The following are a few key notes:

The source code has been commented using TODO to explain the detailed rules you must follow.
There may be more than one way to solve this problem. It is key to demonstrate that your implementation prevents the SQL injection attack and displays the information to the console.
Do not forget that you can leverage capabilities provided by the standard C++ library to help you achieve success.
Please comment on any changes you make in the code to explain the logic, formulas, or data types you are adding. You will also create a brief written summary of the approach taken, why it will stop the SQL Injection Attack, any issues you encountered, and how you resolved those issues.

Specifically, you will prepare the following:

SQL injection defensive coding solutions
C/C++ program functionality and best practices
A summary of your process in a Word document that contains a screenshot of the application console output
To complete this assignment, download the SQL Injection source code files ZIP to use as guidance as you move through the activity. You will use your development environment to complete this activity.
