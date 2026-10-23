extern "C" {
unsigned int fn_8009FFC4(void);
void fn_8009FF94(unsigned int value);
int fn_8011F1A4(void);
int fn_8011F1CC(void);
int fn_8011F37C(void);
void fn_8017D7C4(const char *pText);
}

extern unsigned char lbl_803EA9E0;

/* Scores the play prediction stored by fn_8009FFB4 (1 run, 2
   pass, 3 trick) into the value fn_8009FF94 stores, printing the result
   while lbl_803EA9E0 is set. */
extern "C" void fn_8009FFD4(void)
{
    switch (fn_8009FFC4()) {
    case 0:
        fn_8009FF94(0);
        break;
    case 1:
        if (fn_8011F1A4() && !fn_8011F37C()) {
            fn_8009FF94(1);
            if (lbl_803EA9E0) {
                fn_8017D7C4("Correctly Predicted Run");
            }
        } else {
            fn_8009FF94(2);
            if (lbl_803EA9E0) {
                fn_8017D7C4("Incorrectly Predicted Run");
            }
        }
        break;
    case 2:
        if (fn_8011F1CC() && !fn_8011F37C()) {
            fn_8009FF94(4);
            if (lbl_803EA9E0) {
                fn_8017D7C4("Correctly Predicted Pass");
            }
        } else {
            fn_8009FF94(5);
            if (lbl_803EA9E0) {
                fn_8017D7C4("Incorrectly Predicted Pass");
            }
        }
        break;
    case 3:
        if (fn_8011F37C()) {
            fn_8009FF94(4);
            if (lbl_803EA9E0) {
                fn_8017D7C4("Correctly Predicted Trick");
            }
        } else {
            fn_8009FF94(5);
            if (lbl_803EA9E0) {
                fn_8017D7C4("Incorrectly Predicted Trick");
            }
        }
        break;
    }
}
