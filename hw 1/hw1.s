 .data
nums1:      .word 3,10,5,25,2,8
numsSize1:  .word 6
nums2:      .word 14,70,53,83,49,91,36,80,92,51,66,70
numsSize2:  .word 12

.text
.globl main
main:

    la s0, nums1       # Load address of nums1 into s0
    lw t0, numsSize1   # Load numsSize1 into t0

    jal ra, findMaximumXOR

    # Result is in s1, Print
    mv a0, s1
    li a7, 1           # syscall for print_int
    ecall

    li a0, 10       
    li a7, 11          # syscall for print_char
    ecall

    la s0, nums2       # Load address of nums2 into s0
    lw t0, numsSize2   # Load numsSize2 into t0

    jal ra, findMaximumXOR

    # Result is in s1, Print
    mv a0, s1
    li a7, 1           # syscall for print_int
    ecall

    li a0, 10
    li a7, 11          # syscall for print_char
    ecall

    li a0, 0
    li a7, 93          # syscall for exit
    ecall

# Input:
#   s0: pointer to nums array
#   t0: numsSize
# Output:
#   s1: maxXor

findMaximumXOR:
    li t5, 0          # t5 = maxXor = 0
    li t1, 0          # t1 = i = 0

outer_loop:
    bge t1, t0, end_findMaximumXOR   # if i >= numsSize, end function

    # Load nums[i] into t3
    slli t2, t1, 2    # t2 = i * 4
    add t2, s0, t2    # t2 = address of nums[i]
    lw t3, 0(t2)      # t3 = nums[i]

    # Initialize j = i + 1
    addi t4, t1, 1    # t4 = j = i + 1

inner_loop:
    bge t4, t0, next_i  # if j >= numsSize, move to next i

    # Load nums[j] into a0
    slli t2, t4, 2    # t2 = j * 4
    add t2, s0, t2    # t2 = address of nums[j]
    lw a0, 0(t2)      # a0 = nums[j]

    # Compute a1 = t3 ^ a0
    xor a1, t3, a0

    # Compare a1 with maxXor (t5)
    ble a1, t5, skip_update

    # Update maxXor
    mv t5, a1         # maxXor = a1

skip_update:
    addi t4, t4, 1    # j++
    j inner_loop

next_i:
    addi t1, t1, 1    # i++
    j outer_loop

end_findMaximumXOR:
    mv s1, t5         # s1 = maxXor
    jr ra