var inputs = File.ReadAllLines(@"input.txt").Select(int.Parse).ToList();

var increases = 0;
var prev = inputs[0];
foreach (var input in inputs)
{
    if (input > prev) increases++;

    prev = input;
}

Console.WriteLine($"Increases linear {increases}");


var increases2 = 0;
var prev2 = int.MaxValue;
for (var i = 0; i < inputs.Count; i++)
{
    if (i + 2 < inputs.Count)
    {
        var sum = new[] { inputs[i], inputs[i + 1], inputs[i + 2] }.Sum();

        if (sum > prev2) increases2++;

        prev2 = sum;
    }
}


Console.WriteLine($"Increases for sliding window {increases2}");
