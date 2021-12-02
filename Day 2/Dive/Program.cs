int horizontal = 0, vertical = 0;

File.ReadAllLines(@"input.txt").ToList().ForEach(input =>
{
    var parts = input.Split(' ');
    var amount = int.Parse(parts[1]);

    switch (parts[0])
    {
        case "forward":
            horizontal += amount;
            break;
        default:
            vertical += parts[0] == "up" ? -amount : amount;
            break;
    }
});

Console.WriteLine($"Final Position: h:{horizontal} v:{vertical}, product: {horizontal * vertical}");