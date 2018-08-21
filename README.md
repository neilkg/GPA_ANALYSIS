# GPA Analysis
Created by Neil Gollapudi

**About**
- Command line program allows you to read in a csv file from sources such as and Excel document that contains an updated spreadsheet of your transcript an allows you to predict how your GPA may change with estimated grades in current or future classes.
- Provides average GPA and number of credits by classes taken in one or more department. For example, if user request EECS, the program will give the average GPA and number of credits of all EECS classes taken. If user request EECS and MATH, program will give the average GPA and number of credits of all classes taken in the EECS and MATH department.

<img width="446" alt="screen shot 2018-08-20 at 9 54 57 pm" src="https://user-images.githubusercontent.com/33635204/44375907-11901280-a4c4-11e8-8738-c6abcb6d5135.png">

<img width="213" alt="screen shot 2018-08-20 at 9 56 17 pm" src="https://user-images.githubusercontent.com/33635204/44375909-13f26c80-a4c4-11e8-80bd-db82fd85fe28.png">

<img width="449" alt="screen shot 2018-08-20 at 9 56 39 pm" src="https://user-images.githubusercontent.com/33635204/44375910-1654c680-a4c4-11e8-8511-5343c72076b0.png">

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
