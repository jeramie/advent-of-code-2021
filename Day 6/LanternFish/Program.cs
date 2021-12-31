const int MAX_LIFE = 9;

static long GetCountOfFish(int days)
{
    var fish = File.ReadAllLines(@"input.txt").SelectMany(input => input.Split(',').Select(int.Parse)).GroupBy(f => f)
        .Aggregate(new List<long>(new long[MAX_LIFE]), (list, kv) =>
            {
                list[kv.Key] = kv.Count();
                return list;
            });

    for (var i = 0; i < days; i++)
    {
        var expired = fish[0];

        //shift array to decrement each fishes life
        fish.RemoveAt(0);

        //expired fish are reset to life of 7 (6) days
        fish[6] += expired;

        //each expired fish creates a new fish with life of 9 (8) days
        fish.Add(expired);
    }

    return fish.Sum(c => c);
}

Console.WriteLine($"After 80 days there are now {GetCountOfFish(80)}");

Console.WriteLine($"After 256 days there are now {GetCountOfFish(256)}");