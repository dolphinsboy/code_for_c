cd  glib && make clean
cd ..
cd c_program && make clean
cd ..
cd apue_code 

for dir in `ls`
do
    cd $dir && make clean
    cd ..
done
cd ..
git pull
git add .
git commit -m "$1"
git push
