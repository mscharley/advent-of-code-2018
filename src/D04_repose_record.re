open Belt;

let log = Fs.readFileLinesSync("./input/day4.txt") |> Js.Array.sortInPlace;

Js.log(log);
