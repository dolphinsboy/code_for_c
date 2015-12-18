cd  glib && make clean
cd ..
cd c_program && make clean
cd ..
git add .
git commit -m "$1"
git push
