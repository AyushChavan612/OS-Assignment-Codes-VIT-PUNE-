# string handling functions
#!/bin/bash

echo "Enter a string:"
read str

# Length of string
echo "Length: ${#str}"

# Reverse the string
rev_str=$(echo "$str" | rev)
echo "Reversed: $rev_str"

# Convert to uppercase
upper=$(echo "$str" | tr 'a-z' 'A-Z')
echo "Uppercase: $upper"

# Convert to lowercase
lower=$(echo "$str" | tr 'A-Z' 'a-z')
echo "Lowercase: $lower"

# Check if string is palindrome
if [ "$str" == "$rev_str" ]; then
    echo "The string is a palindrome."
else
    echo "The string is not a palindrome."
fi


# aithmatic functions
#!/bin/bash

echo "Enter two numbers:"
read a
read b

echo "Addition: $((a + b))"
echo "Subtraction: $((a - b))"
echo "Multiplication: $((a * b))"
echo "Division: $((a / b))"
echo "Modulus: $((a % b))"


# palindrome , prime , fibonacci series
#!/bin/bash

echo "Enter a number:"
read num

# 1. Check Palindrome
temp=$num
rev=0
while [ $temp -gt 0 ]
do
    digit=$((temp % 10))
    rev=$((rev * 10 + digit))
    temp=$((temp / 10))
done

if [ $rev -eq $num ]; then
    echo "$num is a Palindrome."
else
    echo "$num is not a Palindrome."
fi

# 2. Check Prime
is_prime=1
if [ $num -le 1 ]; then
    is_prime=0
else
    for ((i = 2; i*i <= num; i++))
    do
        if [ $((num % i)) -eq 0 ]; then
            is_prime=0
            break
        fi
    done
fi

if [ $is_prime -eq 1 ]; then
    echo "$num is a Prime number."
else
    echo "$num is not a Prime number."
fi

# 3. Fibonacci Series
echo "Fibonacci series up to $num terms:"
a=0
b=1
for ((i = 0; i < num; i++))
do
    echo -n "$a "
    fn=$((a + b))
    a=$b
    b=$fn
done
echo
