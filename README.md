#Questions
1. printf('j') - 0xc0000005;
2. scanf_s("%u", &num) - почему при вводе символа выход за пределы массива;
3. ```c
if (position - 1 < FIELD_SIDE * FIELD_SIDE && field[position - 1] == ' ') {
	is_correct = 1;
}
else
{
	printf("Uncorrect enter. Please enter position again: ");
}
```
Почему при маленьких значениях срабатывет только на втором условии, а при больших нужно второе?
И почему при чтении условия не происходит 0xc0000005;