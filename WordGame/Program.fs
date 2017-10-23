open System
open System.Collections.Generic
open System.Linq

///////////////////////////////////////////////////////////////////////////////
// Introduction 
//
// Rules of the game:
// - computer gives a start word (4-character long)
// - the user gives a word in which 1 character has changed 
// - if the user gave correct word computer gives another word with 1 char 
//   changed 
// - and so on...
// - words can't repeat (in such event computer asks for another try)
// - whichever side (you or computer) gave word with no valid words left wins
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Utility functions 
///////////////////////////////////////////////////////////////////////////////

type ValidationResult = 
    | Pass
    | FailWordAlreadyUsed 
    | FailNotRealWord
    | FailMoreThanOneCharChanged

///
/// Prints welcome screen.
///
let printWelcomeScreen () : unit = 
    Console.WriteLine( "======= Word Game =======" )


///
/// Checks whether entered command is not quit command.
///
let isNotQuitCommand ( input : string ) : bool = 
    match input.ToLower() with 
    | "q" -> false 
    | _   -> true 

///
/// Creates a set with all valid 4-letter words.
///
let readAllWords () : HashSet< string > = 
    let words : string[] = System.IO.File.ReadAllLines( @"words.txt" )
    new HashSet< string >( words )

///
/// Gets all words which differ by 1 character from a given word.
/// 
let getCloseWords ( allWords : HashSet< string > ) 
                  ( word     : string ) 
                  : seq< string > = 
    let isClose ( w1 : string ) ( w2 : string ) : bool = 
        if w1 = w2 
        then false 
        else 
            Seq.zip ( w1.ToArray() ) ( w2.ToArray() )
            |> Seq.filter ( fun ( c1, c2 ) -> c1 = c2 )
            |> Seq.length = 3
    allWords
    |> Seq.filter ( isClose word )

///
/// Gets valid next words given words which were already used.
///
let getValidNextWords ( allWords  : HashSet< string > ) 
                      ( usedWords : HashSet< string > ) 
                      ( lastWord  : string )
                      : seq< string > = 
    getCloseWords allWords lastWord
    |> Seq.filter ( fun x -> not ( usedWords.Any( fun y -> y = x ) ) )
    
///
/// Gets next valid word. In case of the beginning og the game word is picked
/// at random.
///
let getNextWord ( allWords  : HashSet< string > ) 
                ( usedWords : HashSet< string > ) 
                ( lastWord : string )
                : option< string > = 
    match lastWord with 
    | "" -> 
        let rnd = new Random()
        let rndIndex = rnd.Next( 1, allWords.Count )
        let word = allWords.ToArray().[ rndIndex ]
        usedWords.Add( word ) |> ignore 
        Some word 
    | _ ->  
        Seq.tryHead <| getValidNextWords allWords usedWords lastWord
        
///
/// Checks whether given word is valid taking into account all valid words as 
/// well as ones which were already used.
///
let isValidWord ( word      : string )
                ( allWords  : HashSet< string > )
                ( usedWords : HashSet< string > ) 
                ( lastWord  : string )
                : ValidationResult = 
    
    if not ( allWords.Contains( word ) )
    then ValidationResult.FailNotRealWord
    else 
        if usedWords.Contains( word ) 
        then ValidationResult.FailWordAlreadyUsed
        else 
            let closeWords = new HashSet< string >( getCloseWords allWords lastWord )
            if closeWords.Contains( word ) 
            then ValidationResult.Pass
            else ValidationResult.FailMoreThanOneCharChanged

let isGetHint ( cmd : string ) : bool = 
    match cmd.ToLower() with 
    | "h" -> true 
    | _   -> false 

///////////////////////////////////////////////////////////////////////////////
// Main 
///////////////////////////////////////////////////////////////////////////////

[<EntryPoint>]
let main argv = 

    let usedWords : HashSet< string > = new HashSet< string >()
    let allWords  : HashSet< string > = readAllWords() 
    let mutable lastWord : string = ""
    let mutable isGameOver : bool = false 

    ///
    /// Reads line from the console. 
    ///
    let readLine ( _ : int ) : string = 
        match isGameOver with 
        | true  -> "q"
        | false -> 
            Console.ForegroundColor <- ConsoleColor.White
            Console.ReadLine()

    let printStartWord () : unit = 
        match getNextWord allWords usedWords lastWord with 
        | Some word -> 
            usedWords.Add( word ) |> ignore 
            lastWord <- word 
            Console.WriteLine( sprintf "We start the game with word: %s" ( word.ToUpper() ) )
        | None -> failwith "Critical error, there are no words in English dictionary!!!"

    printWelcomeScreen()
    printStartWord() 
    // We simulate loop by processing lazy sequence. 
    // Since it is lazy, each user entry is evaluated, until the user enters 
    // quit command. 
    Seq.initInfinite readLine
    |> Seq.takeWhile isNotQuitCommand
    |> Seq.iter ( fun cmd -> 
        match isGetHint cmd, isValidWord cmd allWords usedWords lastWord with 
        | true, _ -> 
            Console.ForegroundColor <- ConsoleColor.Yellow
            Console.WriteLine( "Seriosuly... you need help with this one? I thought you were a pro..." )
            getValidNextWords allWords usedWords lastWord
            |> Seq.iter ( fun x -> 
                Console.WriteLine( x )
            )
        | _, ValidationResult.Pass -> 
            Console.ForegroundColor <- ConsoleColor.Green
            Console.WriteLine( "Word accepted. Well done mate!" )
            usedWords.Add( cmd ) |> ignore

            Console.ForegroundColor <- ConsoleColor.White
            Console.WriteLine( "Computer turn " )
            match getNextWord allWords usedWords lastWord with 
            | Some word -> 
                Console.WriteLine( sprintf "Next word is %s" word )
                lastWord <- word 
                usedWords.Add ( word ) |> ignore 
                match Seq.isEmpty <| getValidNextWords allWords usedWords lastWord with 
                | true -> 
                    Console.ForegroundColor <- ConsoleColor.Red
                    Console.WriteLine( "COMPUTER WON! NO MORE WORDS AVAILABLE" )
                    isGameOver <- true 
                | false -> ()
            | None -> 
                Console.WriteLine( "There are no more valid words." )
                Console.ForegroundColor <- ConsoleColor.Green
                Console.WriteLine( "CONGRATULATIONS! YOU WON!" )
                isGameOver <- true 
        | _, ValidationResult.FailNotRealWord -> 
            Console.ForegroundColor <- ConsoleColor.Red
            Console.WriteLine( "WRONG! This is not a real word! Try again but no cheating this time!" )
        | _, ValidationResult.FailWordAlreadyUsed -> 
            Console.ForegroundColor <- ConsoleColor.Red
            Console.WriteLine( "WRONG! This word was already used! Pay attention mate!" )
        | _, ValidationResult.FailMoreThanOneCharChanged -> 
            Console.ForegroundColor <- ConsoleColor.Red
            Console.WriteLine( "WRONG! More than one chararacter was changed! Is it really too much to ask??" )
    )

    Console.ForegroundColor <- ConsoleColor.White
    Console.WriteLine( "Press any key to close." )
    Console.ReadKey() |> ignore 

    0 // return an integer exit code
