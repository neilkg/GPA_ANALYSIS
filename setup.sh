mkdir GPX_test
cd GPX_test
git init
git pull https://github.com/neilkg/GPA_ANALYSIS
make
mv GPA ~
cd ..
mv GPX_test/grades.csv Desktop/
rm -rf GPX_test
rm setup.sh
