mkdir test
cd test
git init
git pull https://github.com/neilkg/GPA_ANALYSIS
make
mv GPA ~
cd ..
mv test/grades.csv Desktop/
rm -rf test
rm setup.sh
