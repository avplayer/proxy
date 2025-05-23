/*******************************************************
 *                                                     *
 *  -------------------------------------------------  *
 *  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  *
 *  -------------------------------------------------  *
 *  |     0     |     8     |    16     |     24    |  *
 *  -------------------------------------------------  *
 *  |    FS0    |    FS1    |    FS2    |    FS3    |  *
 *  -------------------------------------------------  *
 *  -------------------------------------------------  *
 *  |  8  |  9  |  10 |  11 |  12 |  13 |  14 |  15 |  *
 *  -------------------------------------------------  *
 *  |     32    |    40     |     48    |     56    |  *
 *  -------------------------------------------------  *
 *  |    FS4    |    FS5    |    FS6    |    FS7    |  *
 *  -------------------------------------------------  *
 *  -------------------------------------------------  *
 *  |  16 |  17 |  18 |  19 |  20 |  21 |  22 |  23 |  *
 *  -------------------------------------------------  *
 *  |     64    |    72     |     80    |     88    |  *
 *  -------------------------------------------------  *
 *  |    S0     |    S1     |     S2    |     S3    |  *
 *  -------------------------------------------------  *
 *  -------------------------------------------------  *
 *  |  24 |  25 |  26 |  27 |  28 |  29 |  30 |  31 |  *
 *  -------------------------------------------------  *
 *  |  96 | 100 | 104 | 108 | 112 | 116 | 120 | 124 |  *
 *  -------------------------------------------------  *
 *  |    S4     |    S5     |     S6    |     S7    |  *
 *  -------------------------------------------------  *
 *  -------------------------------------------------  *
 *  |  32 |  33 |  34 |  35 |  36 |  37 |  38 |  39 |  *
 *  -------------------------------------------------  *
 *  | 128 | 132 | 136 | 140 | 144 | 148 | 152 | 156 |  *
 *  -------------------------------------------------  *
 *  |    S8     |    FP     |     RA    |     PC    |  *
 *  -------------------------------------------------  *
 *                                                     *
 * *****************************************************/

.file "make_loongarch64_sysv_elf_gas.S"
.text
.globl make_fcontext
.hidden make_fcontext
.align 2
.type make_fcontext,@function
make_fcontext:
    # shift address in A0 to lower 16 byte boundary
    bstrins.d $a0, $zero, 3, 0

    # reserve space for context-data on context-stack
    addi.d  $a0, $a0, -160

    # third arg of make_fcontext() == address of context-function
    st.d  $a2, $a0, 152

    # save address of finish as return-address for context-function
    # will be entered after context-function returns
    la.local  $a4, finish
    st.d  $a4, $a0, 144

    # return pointer to context-data
    jr  $ra

finish:
    # exit code is zero
    li.d  $a0, 0
    # call _exit(0)
    b  %plt(_exit)

.size make_fcontext, .-make_fcontext
/* Mark that we don't need executable stack.  */
.section .note.GNU-stack,"",%progbits
