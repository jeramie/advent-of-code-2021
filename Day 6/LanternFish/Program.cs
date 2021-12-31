const int MAX_LIFE_SIZE = 9; //size of the collection containing all days of the lifecycle. new fish are added at top of this cycle.
const int RESET_LIFE_IDX = 6; //how many days a re-spawned fish has left (7 days since it is 0 indexed)

static long GetCountOfFish(int days)
{
    var fish = File.ReadAllLines(@"input.txt").SelectMany(input => input.Split(',').Select(int.Parse)).GroupBy(f => f)
        .Aggregate(new List<long>(new long[MAX_LIFE_SIZE]), (list, kv) =>
            {
                list[kv.Key] = kv.Count();
                return list;
            });

    for (var i = 0; i < days; i++)
    {
        var expired = fish.First();

        //shift list to decrement each fishes life
        fish.RemoveAt(0);

        //reset the lifecycle of the expired fish
        fish[RESET_LIFE_IDX] += expired;

        //each expired fish creates a new fish at the top of the life cycle
        fish.Add(expired);
    }

    return fish.Sum(c => c);
}

Console.WriteLine($"After 80 days there are now {GetCountOfFish(80)}");

Console.WriteLine($"After 256 days there are now {GetCountOfFish(256)}");