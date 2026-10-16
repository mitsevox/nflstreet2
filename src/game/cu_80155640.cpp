extern "C" {
int fn_80054568(void);
void fn_800BCB18(void *p, float dt);

void fn_80155640(void *p, float dt)
{
    if (fn_80054568()) {
        fn_800BCB18(p, dt);
    }
}

void fn_801556CC(void)
{
}
}
