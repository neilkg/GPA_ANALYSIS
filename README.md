# GPA Analysis
Created by Neil Gollapudi

**About**
- Command line program allows you to read in a csv file from sources such as and Excel document that contains an updated spreadsheet of your transcript an allows you to predict how your GPA may change with estimated grades in current or future classes.
- Provides average GPA and number of credits by classes taken in one or more department. For example, if user request EECS, the program will give the average GPA and number of credits of all EECS classes taken. If user request EECS and MATH, program will give the average GPA and number of credits of all classes taken in the EECS and MATH department.

<img width="429" alt="screen shot 2018-08-20 at 10 12 52 pm" src="https://user-images.githubusercontent.com/33635204/44376392-574dda80-a4c6-11e8-934f-d9f380c3db0c.png">
<img width="437" alt="screen shot 2018-08-20 at 10 13 28 pm" src="https://user-images.githubusercontent.com/33635204/44376394-59b03480-a4c6-11e8-94b6-d2c920d7978e.png">

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
