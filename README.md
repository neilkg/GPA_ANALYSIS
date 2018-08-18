# GPA Analysis
Created by Neil Gollapudi

**About**
- Command line program allows you to read in a csv file from sources such as an Excel document that contains an updated spreadsheet of your transcript an allows you to predict how your GPA may change with estimated grades in current or future classes.
- Provides average GPA and number of credits by classes taken in one or more department. For example, if user request EECS, the program will give the average GPA and number of credits of all EECS classes taken. If user request EECS and MATH, program will give the average GPA and number of credits of all classes taken in the EECS and MATH department.


**Running Program**
- Download the source code from [github.com/neilkg](https://github.com/neilkg/GPA_ANALYSIS)
```
$ make GPA
$ ./GPA filename.csv
```
&nbsp; 
**Running Program for the Public**
*(Steps 1-3 only need to be done once)*

**1.** Open Terminal

**2.** Enter in these commands (not including '$')
```
$ mkdir test
$ cd test
$ git init
$ git pull https://github.com/neilkg/GPA_ANALYSIS
$ make
$ mv GPA ~
$ cd ..
$ mv test/grades.csv Desktop/
$ rm test
```

**3.** Click on grades.csv on your computer desktop(homepage) and edit the template with your grades.

**4.** Run Program
```
$ ./GPA Desktop/grades.csv
```

**5.** Anytime you want to edit your grades, add to the grades.csv file and Save As

