void multiplyLists(node **multiplicand, node **multiplier, node **result){
    // multiplier digits
    node *currentMultiplierPtr = *multiplier;
    while (currentMultiplierPtr->next != NULL){
            // multiplicand digits
            node *currentMultiplicandPtr = *multiplicand;
            int carry = 0;
            int multiplierIndex = 0;
            while (currentMultiplicandPtr->next != NULL){
                if(index == 0){
                    int value = currentMultiplierPtr->value * currentMultiplicandPtr->value + carry;
                    carry = (value /= 10)%10; // update the carry in here
                    insertNode(result, value%10);
                    currentMultiplicandPtr = currentMultiplicandPtr->next;
                }else{
                    printf("index: %d\n", multiplierIndex);
                }
            }
            // next multiplier digit
            currentMultiplierPtr = currentMultiplierPtr->next;
        }
    return;
}