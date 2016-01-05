cd  glib && make clean
cd ..
cd c_program && make clean
cd ..
cd apue_code && make clean
cd ..
git pull
git add .
git commit -m "$1"
git push
