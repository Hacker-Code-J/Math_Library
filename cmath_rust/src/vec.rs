// vec.rs

use std::fmt;

pub struct Vector {
    pub dim: usize,
    pub elements: std::vec::Vec<f32>,
}

impl Vector {
    pub fn create_default(dim: usize, val: f32) -> Vector {
        Vector {
            dim,
            elements: vec![val; dim],
        }
    }

    pub fn create_empty(dim: usize) -> Vector {
        Vector::create_default(dim, 0.0)
    }

    pub fn new_from_slice(dim: usize, values: &[f32]) -> Vector {
        Vector {
            dim,
            elements: values.to_vec(),
        }
    }
}

impl Clone for Vector {
    fn clone(&self) -> Vector {
        Vector {
            dim: self.dim,
            elements: self.elements.clone(),
        }
    }
}

impl fmt::Display for Vector {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "[ ")?;
        for (i, val) in self.elements.iter().enumerate() {
            if i < self.dim - 1 {
                write!(f, "{}, ", val)?;
            } else {
                write!(f, "{} ", val)?;
            }
        }
        write!(f, "]")
    }
}

