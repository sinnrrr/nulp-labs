fn bisection<F: Fn(f64) -> f64>(f: F, interval: (f64, f64), eps: f64) -> f64 {
    fn calculate_argument(a: f64, b: f64) -> f64 {
        (a + b) / 2.0
    }

    let (mut a, mut b) = interval;

    let mut x = calculate_argument(a, b);

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
    }

    x
}

fn secant<F: Fn(f64) -> f64>(f: &F, interval: (f64, f64), eps: f64) -> f64 {
    fn calculate_argument<F: Fn(f64) -> f64>(f: F, a: f64, b: f64) -> f64 {
        a - (f(a) * (b - a)) / (f(b) - f(a))
    }

    let (mut a, b) = interval;

    let mut current = calculate_argument(f, a, b);
    let mut previous = a;

    loop {
        if (current - previous).abs() < eps {
            break;
        }

        {
            a = current;
            previous = current;
            current = calculate_argument(f, a, b);
        }
    }

    current
}

fn get_eps_input() -> f64 {
    println!("Enter eps value: ");

    let mut buf = String::new();

    std::io::stdin()
        .read_line(&mut buf)
        .ok()
        .expect("Failed reading eps value");

    buf.trim().parse::<f64>().unwrap()
}

fn main() {
    let a = (4.0 - 43.0_f64.sqrt()) / 3.0;
    let b = (4.0 + 43.0_f64.sqrt()) / 3.0;

    fn f(x: f64) -> f64 {
        x.powi(3) - 4.0 * x.powi(2) - 9.0 * x + 2.0
    }

    let eps = get_eps_input();

    println!("{}", bisection(f, (a, b), eps).to_string());
    println!("{}", secant(&f, (a, b), eps).to_string());
}
