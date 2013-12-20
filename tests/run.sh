set -e
do
  bash setup.sh
  ./rmrf target
  ! [ -d target ]
  echo "pass"
done
rm -rf target
