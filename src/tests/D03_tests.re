open D03_no_matter_how_you_slice_it;

let test: 'a. (string, 'a, 'a) => unit =
  (name, expected, input) =>
    if (input != expected) {
      Js.log4("Failed " ++ name ++ ":", input, "!=", expected);
    };

let claim1 = {id: 1, position: {x: 1, y: 3, width: 4, height: 4}};
test(
  "claim1",
  Some(claim1),
  parseClaim("#1 @ 1,3: 4x4"),
);

let claim2 = {id: 2, position: {x: 3, y: 1, width: 4, height: 4}};
test(
  "claim2",
  Some(claim2),
  parseClaim("#2 @ 3,1: 4x4"),
);

let claim3 = {id: 3, position: {x: 5, y: 5, width: 2, height: 2}};
test(
  "claim3",
  Some(claim3),
  parseClaim("#3 @ 5,5: 2x2"),
);

test(
  "claim4",
  Some({id: 4, position: {x: 50, y: 50, width: 20, height: 20}}),
  parseClaim("#4 @ 50,50: 20x20"),
);

let claimMap = [|
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 1, 0,
  0, 1, 1, 2, 2, 1, 1, 0,
  0, 1, 1, 2, 2, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
|];
test(
  "mapClaims",
  claimMap,
  mapClaims([|claim1, claim2, claim3|], 8)->fst,
);

test(
  "part2",
  Some(claim3),
  part2((claimMap, 8), [|claim1, claim2, claim3|]),
);
