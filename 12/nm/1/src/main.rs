use text_io::read;

fn bisection<F: Fn(f64) -> f64>(f: F, interval: (f64, f64), eps: f64) -> (f64, i32) {
    fn calculate_argument(a: f64, b: f64) -> f64 {
        (a + b) / 2.0
    }

    let (mut a, mut b) = interval;

    let mut x = calculate_argument(a, b);

    let mut n = 1;
    loop {
        {
            if (f(a) * f(x)).is_sign_negative() {
                b = x;
            } else {
                a = x
            };

            x = calculate_argument(a, b);
        }

        if f(x) == 0.0 {
            break;
        }

        if (b - a).abs() < eps {
            break;
        }

        n += 1;
    }

    (x, n)
}

fn secant<F: Fn(f64) -> f64>(f: &F, interval: (f64, f64), eps: f64) -> (f64, i32) {
    fn calculate_argument<F: Fn(f64) -> f64>(f: F, a: f64, b: f64) -> f64 {
        a - (f(a) * (b - a)) / (f(b) - f(a))
    }

    let (mut a, b) = interval;

    let mut current = calculate_argument(f, a, b);
    let mut previous = a;

    let mut n = 1;
    loop {
        if (current - previous).abs() < eps {
            break;
        }

        {
            a = current;
            previous = current;
            current = calculate_argument(f, a, b);
        }

        n += 1;
    }

    (current, n)
}

fn main() {
    fn f(x: f64) -> f64 {
        x.powi(3) - 4.0 * x.powi(2) - 9.0 * x + 2.0
    }

    println!("\nEnter a value: ");
    let a: f64 = read!();

    println!("\nEnter b value: ");
    let b: f64 = read!();

    println!("Enter eps value: ");
    let eps: f64 = read!();

    if (f(a) * f(b)) > 0.0 {
        eprintln!("\nNo valid x in this bounds");

        std::process::exit(1);
    }

    let bisection_result = bisection(f, (a, b), eps);
    let secant_result = secant(&f, (a, b), eps);

    println!(
        "\n\nBisection method: {} (iterations: {})",
        bisection_result.0.to_string(),
        bisection_result.1.to_string()
    );
    println!(
        "Secant method: {} (iterations: {})",
        secant_result.0.to_string(),
        secant_result.1.to_string()
    );
}
