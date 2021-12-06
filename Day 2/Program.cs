var inputs = File.ReadAllLines(@"input.txt").Select(line => line.Split(' ') switch { var a => (Direction: a[0], Amount: int.Parse(a[1])) }).ToList();


//challenge 1
var (horizontal, vertical) = inputs.Aggregate((Horizontal: 0, Vertical: 0), (total, next) =>
{
    var (direction, amount) = next;

    if (direction == "forward")
    {
        total.Horizontal += amount;
    }
    else
    {
        total.Vertical += direction == "up" ? -amount : amount;
    }

    return total;
});

Console.WriteLine($"Final Product {horizontal * vertical}");

//challenge 2
var (horizontal1, vertical1, _) = inputs.Aggregate((Horizontal: 0, Vertical: 0, Aim: 0), (total, next) =>
{
    var (direction, amount) = next;

    if (direction == "forward")
    {
        total.Horizontal += amount;
        total.Vertical += total.Aim * amount;
    }
    else
    {
        total.Aim += direction == "up" ? -amount : amount;
    }

    return total;
});

Console.WriteLine($"Final Product {horizontal1 * vertical1}");