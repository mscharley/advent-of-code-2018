open D02_inventory_management_system;

let test: 'a. (string, 'a, 'a) => unit =
  (name, input, expected) =>
    if (input != expected) {
      Js.log4("Failed " ++ name ++ ":", input, "!=", expected);
    };

test(
  "summarise1",
  summarise("abcdef") |> Js.Dict.entries,
  [|("a", 1), ("b", 1), ("c", 1), ("d", 1), ("e", 1), ("f", 1)|],
);

test(
  "summarise2",
  summarise("bababc") |> Js.Dict.entries,
  [|("b", 3), ("a", 2), ("c", 1)|],
);

test(
  "summarise3",
  summarise("abbcde") |> Js.Dict.entries,
  [|("a", 1), ("b", 2), ("c", 1), ("d", 1), ("e", 1)|],
);

test(
  "testPart1",
  part1([|
    "abcdef",
    "bababc",
    "abbcde",
    "abcccd",
    "aabcdd",
    "abcdee",
    "ababab",
  |]),
  (4, 3),
);

test("distance1", idsDistance("abcde", "axcye"), (2, "ace"));

test("distance2", idsDistance("fghij", "fguij"), (1, "fgij"));

test(
  "part2",
  part2(["abcde", "fghij", "klmno", "pqrst", "fguij", "axcye", "wvxyz"]),
  Some("fgij"),
);
