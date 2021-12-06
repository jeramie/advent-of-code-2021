var inputs = File.ReadAllLines(@"input.txt").Select(int.Parse).ToList();

//challenge 1
Console.WriteLine($"Increases for linear {inputs.Where((input, idx) => idx > 0 && input > inputs[idx - 1]).Count()}");

//challenge 2
Console.WriteLine($"Increases for sliding window {inputs.Where((_, idx) => idx > 0 && idx + 2 < inputs.Count && inputs.GetRange(idx, 3).Sum() > inputs.GetRange(idx - 1, 3).Sum()).Count()}");