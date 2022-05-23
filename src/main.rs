use std::env;

fn check_arg_len(args: &Vec<String>) {
    match args.len() {
        2 => {
            if args[1] == "-h" {
                println!("USAGE\n    ./209poll pSize sSize p\n\nDESCRIPTION\n    pSize   size of the population\n    sSize   size of the sample (supposed to be representative)\n    p       percentage of voting intentions for a specific candidate");
                std::process::exit(0);
            }
            std::process::exit(84);
        },
        4 => (),
        _ => std::process::exit(84),
    }
}

fn get_arg_as_number(args: &Vec<String>) -> (u32, u32, f32) {
    let pop: u32 = match args[1].parse::<u32>() {
        Ok(num) => num,
        Err(_) => {
            eprintln!("Error: first argument is not a int");
            std::process::exit(84);
        }
    };
    let size: u32 = match args[2].parse::<u32>() {
        Ok(num) => num,
        Err(_) => {
            eprintln!("Error: second argument is not a int");
            std::process::exit(84);
        }
    };
    let p: f32 = match args[3].parse::<f32>() {
        Ok(num) => num,
        Err(_) => {
            eprintln!("Error: third argument is not a int");
            std::process::exit(84);
        }
    };
    return (pop, size, p);
}

fn calc_variance(pop: f32, size: f32, p: f32) -> f32 {
    return (p / size) * (1.0 - p) * ((pop - size) / (pop - 1.0));
}

fn main() {
    let args: Vec<String> = env::args().collect();
    check_arg_len(&args);
    let (pop, size, p) = get_arg_as_number(&args);
    if p > 100.0 || 0.0 > p {
        std::process::exit(84);
    }
    println!("Population size:         {}", pop);
    println!("Sample size:             {}", size);
    println!("Voting intentions:       {:.2}%", p);
    let deviation: f32 = calc_variance(pop as f32, size as f32, p / 100.0);
    println!("Variance:                {:.6}", deviation);
    println!("95% confidence interval: [{:.2}%; {:.2}%]", if 0.0 > (p - 100.0 * (deviation.sqrt() * 1.96)) {0.0} else {p - 100.0 * (deviation.sqrt() * 1.96)}, if p + 100.0 * (deviation.sqrt() * 1.96) > 100.0 {100.0} else {p + 100.0 * (deviation.sqrt() * 1.96)});
    println!("99% confidence interval: [{:.2}%; {:.2}%]", if 0.0 > (p - 100.0 * (deviation.sqrt() * 2.58)) {0.0} else {p - 100.0 * (deviation.sqrt() * 2.58)}, if p + 100.0 * (deviation.sqrt() * 2.58) > 100.0 {100.0} else {p + 100.0 * (deviation.sqrt() * 2.58)});
}