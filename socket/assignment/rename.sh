for i in 6 8 9 10 11 12 13 14 15 16 17 18 41 61
do
  echo "renamed $i"
  cd $i
  mv client.cpp client.c
  mv server.cpp server.c
  cd ..
done