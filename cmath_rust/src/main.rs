mod config;
use config::num_args;

mod vec; // Include the vec module
use vec::Vector; // Use the Vec struct from the vec module

fn main() {
    // Example usage
    let count = num_args(&[1, 2, 3, 4]);
    println!("Number of arguments: {}", count);

    let v = Vector::create_default(5, 1.25);
    println!("{}", v); // Display the vector

    let empty_v = Vector::create_empty(3);
    println!("{}", empty_v);

    let from_slice_v = Vector::new_from_slice(5, &[1.0, 2.0, 3.0, 4.0, 5.0]);
    println!("{}", from_slice_v);

    let copied_v = from_slice_v.clone();
    println!("{}", copied_v);
}