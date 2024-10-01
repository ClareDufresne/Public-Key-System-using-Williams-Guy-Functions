use std::mem::swap;
use std::ops::{RemAssign, ShrAssign};

use num_bigint::BigInt;
use num_integer::Integer;
use num_traits::{One, Signed, Zero};

#[no_mangle]

pub extern "C" fn jacobi_new(num1: &i32, num2: &i32) -> i8 {
    let a: &BigInt = &BigInt::from(*num1);
    let m: &BigInt = &BigInt::from(*num2);
    
    if !m.is_positive() || m.is_even() {
        eprintln!("Jacobi Invalid input");
    }

    // After the reduction, we know that both a and m are positive
    let mut a = a.mod_floor(m).into_parts().1;
    let mut m = m.magnitude().clone();

    // The output
    let mut t = true;

    // The second bit of m (will be a after swap)
    let mut m_2 = m.bit(1);

    while !a.is_zero() {
        // Remove all trailing zeros from a and adjust t accordingly
        let trailing_zeros = a.trailing_zeros().expect("a is not zero");
        if !trailing_zeros.is_zero() {
            a.shr_assign(trailing_zeros);
        }

        let a_2 = a.bit(1);
        if (trailing_zeros.is_odd() && (m_2 ^ m.bit(2))) ^ (m_2 && a_2) {
            t = !t;
        }


        // Swap a and m
        m_2 = a_2;
        swap(&mut a, &mut m);
        a.rem_assign(&m);
    }

    if m.is_one() {
        if t {
            return 1;
        }
        else {
            return -1;
        }
    }
    0
}

pub fn jacobi_num_bigint_dig(a: &num_bigint_dig::BigInt, m: &num_bigint_dig::BigInt) -> Option<i8> {
    if !m.is_positive() || m.is_even() {
        return None;
    }
    Some(num_bigint_dig::algorithms::jacobi(a, m) as i8)
}