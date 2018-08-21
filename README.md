# GPA Analysis
Created by Neil Gollapudi

**About**
- Command line program allows you to read in a csv file from sources such as and Excel document that contains an updated spreadsheet of your transcript an allows you to predict how your GPA may change with estimated grades in current or future classes.
- Provides average GPA and number of credits by classes taken in one or more department. For example, if user request EECS, the program will give the average GPA and number of credits of all EECS classes taken. If user request EECS and MATH, program will give the average GPA and number of credits of all classes taken in the EECS and MATH department.

<img width="444" alt="screen shot 2018-08-20 at 9 42 25 pm" src="https://user-images.githubusercontent.com/33635204/44375611-8d895b00-a4c2-11e8-83d2-9f8ed59077b3.png">

<img width="228" alt="screen shot 2018-08-20 at 9 43 59 pm" src="https://user-images.githubusercontent.com/33635204/44375664-d04b3300-a4c2-11e8-9cf1-5619a6deb93d.png">

**Setup:**
* Enter in Terminal (not including '$')
```
$ curl -OL https://github.com/neilkg/GPA_ANALYSIS/raw/master/setup.sh
$ chmod 700 setup.sh
$ ./setup.sh
```
* Click on grades.csv on your computer desktop(homepage) and edit the template with your grades.

**Run Program:**
```
$ ./GPA Desktop/grades.csv
```
