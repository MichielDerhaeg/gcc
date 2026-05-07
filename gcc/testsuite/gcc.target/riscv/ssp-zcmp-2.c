/* Verify that when Zcmp selects cm.push/cm.pop for prologue/epilogue,
   the Zicfiss shadow-stack check is preserved by avoiding the fused
   cm.popret form.  */

/* { dg-do compile } */
/* { dg-options "-Os -march=rv32g_zcmp_zcmop_zicfiss -mabi=ilp32d -fcf-protection=return" } */
/* { dg-skip-if "needs -Os" { *-*-* } { "-O0" "-O1" "-O2" "-O3" "-Og" "-Oz" } { "" } } */

int printf (const char *, ...);

int printSomething (int arr[], int len) {
  for (int i = 0; i < len; i++)
    printf ("Val[%d]: %d\n", i, arr[i]);
  return len;
}

/* { dg-final { scan-assembler "cm\\.push" } } */
/* { dg-final { scan-assembler "cm\\.pop\[ \t\]" } } */
/* { dg-final { scan-assembler-not "cm\\.popret" } } */
/* { dg-final { scan-assembler "sspush\tra" } } */
/* { dg-final { scan-assembler "sspopchk\tra" } } */

/* Interrupt handlers must not use cm.push but must still emit sspopchk.  */
extern void bar (void);
void __attribute__ ((interrupt))
isr (void)
{
  bar ();
}

/* The interrupt handler should not use the Zcmp multi-push path, so cm.push
   appears at most once (from printSomething).  */
/* { dg-final { scan-assembler-times "cm\\.push" 1 } } */
