#!/bin/bash

# checker pentru calculator

cd ..

STRING="print("
STRING2="print(int(result) if result.is_integer() else round(result, 5))"
OUT_FILE="tests/output.out"
REF_FILE="tests/output.ref"

# curatare fisiere de output
echo -n "" > "$OUT_FILE"
echo -n "" > "$REF_FILE"

# pentru fisierul ref
while IFS= read -r line; do
    REZULTAT=$(echo "$STRING$line)" | python3)
    echo "print(int($REZULTAT) if float($REZULTAT).is_integer() else round($REZULTAT, 5))" | python3 >> "$REF_FILE"
done < tests/tests_bc

# se compileaza
make

# pentru fisierul out
while IFS= read -r _; do
    ./main >> "$OUT_FILE"
    echo -ne "exit\n"
done < tests/tests_calculator

diff $OUT_FILE $REF_FILE

if [ $? -eq 0 ]; then
    echo "Totul este corect"
else 
    echo "Ceva este gresit"
fi

cd tests
