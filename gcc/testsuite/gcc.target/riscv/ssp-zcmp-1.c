/* Verify that sspopchk is emitted in epilogues that use the Zcmp
   cm.push/cm.pop sequence for register save/restore.  When Zcmp was
   enabled together with Zicfiss, the combined cm.popret form was selected
   and the shadow-stack check was lost.  */

/* { dg-do compile } */
/* { dg-options "-march=rv32g_zcmp_zcmop_zicfiss -mabi=ilp32d -fcf-protection=return" } */

int printf (const char *, ...);

int printSomething (int arr[], int len) {
  for (int i = 0; i < len; i++)
    printf ("Val[%d]: %d\n", i, arr[i]);
  return len;
}

/* Interrupt handlers must not use cm.push/cm.pop, but they still need a
   shadow-stack check.  Verify that sspush/sspopchk are emitted via the
   regular save/restore path.  */
extern void bar (void);
void __attribute__ ((interrupt))
isr (void)
{
  bar ();
}

/* Both functions must emit sspush/sspopchk on ra.  printSomething pops ra
   into ra (cm.pop) or t0 (regular ld) depending on whether Zcmp was
   selected; either way sspopchk must be present.  isr always uses regular
   restores.  cm.popret must never be selected when zicfiss is active.  */
/* { dg-final { scan-assembler-times "sspush\tra" 2 } } */
/* { dg-final { scan-assembler-not "cm\\.popret" } } */

