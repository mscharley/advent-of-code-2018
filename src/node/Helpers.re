open Belt;

let chars_of_string: string => array(string) = Js.String.split("");

let recoverOption: 'a. (option('a), unit => option('a)) => option('a) =
  (o, fn) =>
    switch (o) {
    | Some(_) as value => value
    | None => fn()
    };

let countElements = (arr, fn) => arr->Array.reduce(0, (acc, v) => acc + (if (fn(v)) 1 else 0));
