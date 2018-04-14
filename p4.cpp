// Author: Forrest Miller
// Filename: p4.cpp (includes main() for p4)
// Date: November 15, 2017
// Version: 1.0
// References:
//    For Getting User Input:
//         http://www.cplusplus.com/reference/istream/istream/peek/

#include <iostream>
#include "SequenceEnum.h"
#include "SeqExtract.h"
#include "SpasEnum.h"
#include <stdint.h>//Allows for the additional integer types (uint,uint8_t,etc)
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h> /* Random Number Generation */
#include <vector>

using std::string;
using std::cout;

// Description: This driver program consists of a guessing game where a player
//              initially choses a wordLength in letters to get a catagory of
//              potential words to chose from. The program then gives the user
//              the result of a SequenceEnum-type object's affect on that
//              randomly chosen word, and the user gets 3 chances to guess what
//              the original word was. Score is kept for right/wrong answers.
//              Entering 0 for a word length will cause the program to quit.
//
//  WARNING: I took the advice to not skimp on my driver to heart. This driver
//           has quite a bit of functionality and content to it, allowing it to
//           showcase the full potential of the SequenceEnum objects.
//
// Intended Use: This driver is intended to showcase the full power of the
//               sequenceEnum hierarchy of objects when it comes to powering a
//               high-intensity guessing game involving a large catagory of
//               answers to choose from. It also is intended to show that the
//               sequenceEnum hierarchy of objects has been set up correctly to
//               take advantage of inheritance and polymorphism.
//
// User-Interface: The user-interface should be pretty self-explanitory, but
//                 essentially the user is anticipated to have access to a
//                 keyboard that allows him/her/they to enter both letters and
//                 numbers as input. Anytime user input is required, the program
//                 will clearly state what is/isn't acceptable input for each
//                 prompt. In fact, if the user enters input that does not
//                 confrom to what the driver program is looking for at that
//                 instance, the user input is echoed to the screen with a
//                 chance to try to re-enter correct input.
//
// Intent of Driver: This driver is intended for use by people who are very very
//                    bored and want to work on their word-knowledge skills.
//                   While the timeframe for this project limited how much
//                   material could be placed in the word arrays to draw
//                  potential words to SequenceEnumerate upon, it was invisioned
//                   that this driver could eventually support having the entire
//                   English (and perhaps French) languages encapsulated within
//                   it to allow for the full potential of the SequenceEnum
//                   family of objects to be realized. Alas, this driver will
//                   never reach its true intent, so we must learn to accept it
//                   in its current form.
//
// Structure of Driver: The driver is structured like a guessing game. In a
//                      guessing game, players guess, and their guesses are
//                      either right or wrong. This driver tracks the number of
//                      times the user is right or is wrong, and prints out the
//                      information as statistics that are superbly formatted.
//                      The driver's structure also allows the user to enter '0'
//                      to terminate execution of the program between guessing
//                      activities.
//
// Assumptions:  A fairly competent grasp of the English language is assumed to
//               be possessed by the user, without it I imagine playing this
//               guessing game will be fairly hard (there are definitily some
//               obscure words in here, don't worry though if you aren't doing
//               well, I myself was wrong more often than not).
//               It is also assumed that the user will not be wishing to guess
//               words that are longer than 12 letters, because that is the
//               current maximum wordlength this driver supports for guessing.


//--------------------------------------------------------------------
//  Constants
//--------------------------------------------------------------------

const int MAX_PREDEFINED_WORD_LENGTH = 13; //This is for array to hold count of
//                                         words of each length
const int MAX_GUESSES = 3;
const int DO_SEQ_ENUM = 0;
const int DO_SEQ_EXTRACT = 1;
const int SECND_LTR_OF_WRD_INDX = 1; //string.at(1) is second letter
const int SEQ_ENUM_VARIANTS = 3; //3 types of sequence enum
const int ZERO_LETTERS = 0;
const int ONE_LETTER = 1;
const int TWO_LETTERS = 2;
const int THREE_LETTERS = 3;
const int FOUR_LETTERS = 4;
const int FIVE_LETTERS = 5;
const int SIX_LETTERS = 6;
const int SEVEN_LETTERS = 7;
const int EIGHT_LETTERS = 8;
const int NINE_LETTERS = 9;
const int TEN_LETTERS = 10;
const int ELEVEN_LETTERS = 11;
const int TWELVE_LETTERS = 12;
const float ONE_HUNDRED_PERCENT = 100.0;
const float FIFTY_PERCENT = 50.0;

//static const string longWord = "Floccinaucinihilipilification";

//Note to grader: I have a lot of test words to ensure my objects opperate
//                flawlessly and to keep the driver's game interesting. Please
//                just skip past these massive static arrays of words

static const string wrd3Ltr[] ={"ace", "ant", "are", "axe", "bar", "bed", "bag",
    "bat", "bow", "bus", "bug", "can", "car", "cat", "cub", "cup", "dig", "dog",
    "dug", "duo", "eat", "eve", "fad", "far", "fur", "fun", "fix", "gap", "gig",
    "gym", "hen", "hog", "hot", "ice", "ill", "ick", "jab", "jaw", "jam", "jog",
    "joy", "jug", "key", "kid", "kit", "lab", "lag", "law", "lay", "let", "lid",
    "lie", "lot", "lug", "lye", "mad", "man", "mat", "map", "met", "mic", "mid",
    "mix", "mom", "mud", "mop", "nag", "nap", "net", "new", "nod", "not", "nun",
    "nut", "oak", "oar", "oat", "odd", "off", "oil", "old", "one", "ore", "our",
    "orb", "out", "owe", "own", "pad", "pan", "pat", "put", "pay", "pen", "pet",
    "pew", "pie", "pig", "pop", "pot", "pro", "pie", "pun", "put", "rag", "ram",
    "ran", "rat", "ray", "rob", "rot", "rub", "rug", "rum", "run", "sad", "sag",
    "sat", "saw", "see", "sea", "set", "she", "sip", "sit", "six", "sky", "ski",
    "sly", "spy", "sow", "spa", "sum", "sun", "tab", "tad", "tag", "tea", "ten",
    "tax", "the", "tie", "tip", "too", "top", "try", "tow", "two", "urn", "use",
    "vat", "vet", "via", "vex", "wad", "wag", "was", "way", "wax", "win", "won",
    "who", "win", "wit", "wow", "wry", "yak", "yam", "yay", "yup", "yes", "yet",
    "yew", "yum", "zap", "zig", "zip", "zoo", "uke", "ale", "air", "ape", "and",
    "art", "bog", "boy", "bot", "cow", "dud", "elk", "fib", "fig", "fog", "gum",
    "gun", "hug", "hen", "hop", "int", "its", "jar", "bun", "bum", "ode", "rid",
    "rod", "why", "yaw",
}; //Word ideas from http://www.wordfind.com/3-letter-words/

static const string wrd4Ltr[] = {"able", "aced", "ache", "acid", "acre", "acts",
    "adds", "aero", "afar", "ajar", "aged", "ages", "ahoy", "aide", "akin",
    "ally", "alms", "alps", "also", "amid", "ammo", "anew", "anti", "ants",
    "apes", "apex", "arch", "area", "army", "ashy", "asks", "atom", "atop",
    "aunt", "aura", "auto", "avid", "away", "axle", "axes", "baby", "back",
    "bags", "bail", "bait", "bake", "bald", "balk", "ball", "balm", "band",
    "bang", "bank", "bans", "bard", "bare", "base", "bass", "bash", "bask",
    "bath", "bats", "bawl", "bays", "bead", "beak", "beam", "bean", "bear",
    "beat", "beds", "beef", "been", "beep", "beer", "bees", "begs", "bell",
    "belt", "bend", "bent", "best", "bets", "bias", "bide", "bike", "bill",
    "bins", "bile", "bind", "bios", "bird", "bite", "bits", "blip", "blob",
    "blog", "blow", "blub", "blue", "blur", "boar", "boat", "body", "bogs",
    "boil", "bold", "bolt", "bomb", "bond", "bone", "bonk", "bony", "book",
    "boom", "boot", "born", "boss", "both", "bout", "bowl", "bows", "boys",
    "brag", "brat", "bred", "brig", "brow", "brew", "brim", "bulk", "bull",
    "bump", "bunk", "buns", "buoy", "bunt", "burn", "bury", "buts", "buys",
    "buzz", "bush", "burp", "burg", "busk", "bust", "busy", "byte", "cage",
    "cake", "calf", "call", "calm", "camp", "came", "cane", "cans", "cape",
    "carb", "card", "care", "cars", "case", "cash", "cast", "cats", "cave",
    "cart", "cede", "cell", "cent", "chai", "chap", "char", "chat", "chef",
    "chew", "chin", "chip", "chop", "chow", "chum", "cite", "city", "clad",
    "clam", "clan", "clap", "claw", "clay", "clef", "clip", "clog", "clop",
    "clot", "club", "clue", "coal", "coax", "code", "coif", "coil", "coin",
    "cola", "cold", "coma", "comb", "come", "cone", "cook", "cool", "cope",
    "cops", "copy", "cord", "core", "cork", "corn", "cost", "coup", "cove",
    "cowl", "cows", "crab", "cram", "crap", "cred", "crib", "crew", "crop",
    "crow", "crud", "cube", "cues", "cuff", "cull", "cups", "curb", "cure",
    "curl", "cusp", "cute", "cuts", "cyan", "czar", "cyst", "daft", "dame",
    "damp", "dams", "dang", "dank", "dare", "dark", "darn", "dart", "dash",
    "data", "date", "dawn", "days", "daze", "dead", "deaf", "deal", "dear",
    "debt", "deck", "deed", "deem", "deep", "deer", "deft", "defy", "deli",
    "delt", "demo", "dent", "deny", "desk", "dial", "dibs", "dice", "died",
    "dies", "diet", "digs", "dime", "dine", "dink", "dips", "dire", "dirt",
    "disc", "disk", "diss", "dive", "dock", "docs", "doer", "does", "dogs",
    "doll", "dome", "done", "doom", "door", "dope", "dorm", "dose", "dove",
    "down", "doze", "drab", "drag", "drat", "draw", "drew", "drip", "drop",
    "drug", "drys", "daud", "dual", "dubs", "duck", "duct", "dude", "duds",
    "deul", "dues", "duet", "duke", "dull", "dumb", "dump", "dune", "dung",
    "dunk", "duos", "dupe", "dusk", "dust", "duty", "dyad", "dyed", "dyes",
    "each", "earn", "ears", "ease", "east", "easy", "eats", "echo", "eddy",
    "edge", "edgy", "edit", "eels", "eery", "egad", "eggs", "eggy", "egis",
    "elks", "ekes", "else", "ends", "envy", "eons", "epic", "even", "ever",
    "evil", "exam", "exec", "exes", "exit", "expo", "eyed", "eyes", "eyre",
    "face", "fact", "fade", "fads", "fail", "fair", "fake", "fall", "fame",
    "fane", "fang", "fans", "fare", "farm", "fast", "fate", "faze", "fear",
    "feat", "feed", "feel", "feet", "fell", "felt", "fend", "fess", "fest",
    "feta", "feud", "fibs", "fife", "figs", "file", "fill", "film", "find",
    "fine", "fink", "fire", "firm", "firn", "fish", "fist", "fits", "five",
    "fizz", "flab", "flag", "flak", "flap", "flat", "flaw", "flax", "flay",
    "flea", "fled", "flee", "flew", "flex", "flic", "flip", "floc", "flog",
    "flow", "flub", "flue", "flux", "foam", "foci", "foes", "fogs", "foil",
    "fold", "folk", "fond", "font", "food", "fool", "foot", "fork", "form",
    "fort", "fore", "fork", "form", "fort", "foul", "four", "fowl", "foxy",
    "frag", "fray", "free", "fret", "frog", "from", "fuel", "full", "fume",
    "fund", "funk", "fury", "fuse", "fuss", "futz", "fuze", "fuzz", "gags",
    "gain", "gang", "gait", "gate", "gage", "game", "gape", "gasp", "gave",
    "gawk", "gaze", "gear", "geek", "gent", "gets", "gibs", "gift", "gigs",
    "gill", "gild", "girl", "give", "glee", "glob", "glop", "glow", "glue",
    "glug", "glum", "gnat", "goad", "goal", "goat", "gobs", "gods", "goes",
    /*   */ "golf", "gone", "gong", "good", "goof", "goop", "gore", "gory",
    "gosh", "gout", "gown", "grab", "grad", "gram", "gray", "grew", "grey",
    "grey", "grid", "grip", "grow", "grub", "gulf", "gull", "gulp", "gums",
    "gunk", "guns", "gush", "gust", "guts", "guys", "gyms", "gyro", "hack",
    "haft", "haha", "hail", "hair", "half", "hall", "halo", "halt", "hand",
    "hang", "hard", "hark", "harp", "hash", "hast", "hate", "hath", "hats",
    "have", "hawk", "haze", "hays", "hazy", "head", "heal", "heap", "hear",
    "heat", "heck", "heed", "heel", "heft", "heir", "held", "hell", "helm",
    "helm", "help", "hemp", "hens", "herb", "here", "hero", "hers", "hest",
    "hick", "hide", "high", "hike", "hill", "hilt", "hims", "hind", "hint",
    "hips", "hire", "hiss", "hits", "hive", "hoax", "hobo", "hobs", "hold",
    "hole", "holm", "holy", "hope", "home", "homy", "hone", "honk", "hoop",
    "hoot", "hope", "hops", "hood", "horn", "hose", "host", "host", "hots",
    "hour", "hove", "howl", "hows", "hubs", "huck", "huff", "huge", "hugs",
    "hulk", "hull", "hump", "hums", "hung", "hunk", "hunt", "hurl", "hurt",
    "hush", "husk", "huts", "hymm", "hype", "hypo", "ibex", "ibis", "iced",
    "ices", "ichs", "icky", "icon", "idea", "ides", "idle", "idol", "idyl",
    "iffy", "ikon", "ills", "illy", "imam", "imps", "inch", "info", "inks",
    "inky", "into", "ions", "iota", "iris", "irks", "iron", "isle", "itch",
    "item", "jabs", "jack", "jade", "jail", "jams", "jarl", "jars", "java",
    "jaws", "jays", "jazz", "jeep", "jeer", "jest", "jets", "jibe", "jews",
    "jigs", "jinx", "jobs", "john", "join", "joke", "jolt", "jots", "jowl",
    "joys", "judo", "jugs", "juke", "jump", "junk", "jury", "just", "kale",
    "kail", "kapa", "keel", "keen", "keep", "kelp", "kelt", "kept", "keys",
    "khan", "kick", "kids", "kill", "kilo", "kilt", "kind", "king", "kink",
    "kiss", "kite", "kits", "kiwi", "knap", "knee", "knew", "knit", "knob",
    "knot", "know", "konk", "kudo", "labs", "lack", "lacy", "lads", "lady",
    "lags", "laid", "lair", "lake", "lama", "lamb", "lame", "lamp", "lams",
    "land", "lane", "lank", "laps", "lard", "lark", "lash", "last", "late",
    "lava", "lawn", "laws", "lays", "laze", "lazy", "lead", "leaf", "leak",
    "lean", "leap", "leek", "leer", "left", "legs", "lens", "lent", "lept",
    "less", "lest", "lets", "levy", "lewd", "liar", "lice", "lick", "lids",
    "lies", "life", "lift", "like", "limb", "lime", "limp", "line", "link",
    "lint", "lion", "lips", "lisp", "list", "lite", "live", "load", "loaf",
    "loan", "lobe", "lock", "loft", "logo", "logs", "lone", "long", "look",
    "loon", "loop", "loot", "lord", "lore", "lorn", "lose", "loss", "lost",
    "lots", "loud", "love", "lube", "luck", "lugs", "lump", "lung", "lunk",
    "lure", "lush", "lust", "lute", "lynx", "mach", "macs", "made", "mage",
    "made", "mags", "maid", "mail", "maim", "make", "male", "mall", "malt",
    "mama", "mana", "many", "maps", "mark", "mart", "mash", "mask", "mass",
    "mast", "mate", "math", "mats", "maul", "maws", "mayo", "maze", "mead",
    "meal", "mean", "meat", "meds", "meek", "meet", "mega", "meld", "melt",
    "memo", "mend", "menu", "meow", "mesh", "mess", "mice", "mics", "mike",
    "mild", "mile", "milk", "mill", "mime", "mind", "mine", "mink", "mint",
    "miss", "mist", "moan", "moat", "mode", "mods", "mold", "mole", "moms",
    "monk", "mono", "momy", "mood", "moon", "moot", "mope", "mops", "more",
    "morn", "moss", "most", "moth", "move", "much", "muck", "muds", "muff",
    "mugs", "mule", "mull", "mumm", "mump", "muon", "muse", "much", "muck",
    "mush", "muck", "must", "mute", "muts", "myth", "naan", "nabs", "nada",
    "nail", "name", "naps", "navy", "near", "neat", "neck", "need", "neon",
    "nerd", "nest", "nets", "news", "next", "nice", "nick", "nill", "nine",
    "nite", "nips", "nits", "node", "nods", "nose", "noir", "none", "nook",
    "noon", "nope", "norm", "nose", "note", "noun", "nova", "nude", "nuke",
    "null", "numb", "nuns", "nuts", "oafs", "oaks", "oars", "oath", "oats",
    "obey", "oboe", "odds", "odor", "ogle", "ogre", "odes", "offs", "ohms",
    "oils", "oily", "oink", "okay", "olds", "omen", "omit", "once", "ones",
    "only", "onto", "onus", "onyx", "oohs", "oops", "ooze", "opal", "open",
    "opts", "oral", "orbs", "orca", "orcs", "ores", "otto", "ouch", "ours",
    "oust", "outs", "oval", "oven", "over", "owed", "owes", "owls", "owns",
    "oxen", "oxes", "oyez", "pace", "pack", "pact", "pads", "page", "paid",
    "pail", "pain", "pair", "pale", "palm", "pane", "pang", "pant", "papa",
    "pare", "park", "part", "pass", "past", "path", "pave", "pawn", "paws",
    "pays", "peak", "peal", "pear", "peas", "peat", "peck", "peek", "peel",
    "peep", "peer", "pegs", "pend", "peon", "perk", "perp", "peso", "pest",
    "pets", "pews", "pfft", "phew", "pick", "pied", "pier", "pies", "pigs",
    "pike", "pile", "pill", "pine", "ping", "pink", "pins", "pint", "pion",
    "pipe", "pips", "pish", "pita", "pits", "pity", "plan", "play", "plea",
    "pleb", "plex", "plie", "plod", "plop", "plot", "ploy", "plug", "plum",
    "plus", "pods", "poem", "poet", "poke", "pole", "poll", "polo", "poly",
    "pomp", "poms", "pond", "pong", "pony", "poof", "pooh", "pool", "poop",
    "poor", "pope", "pops", "pore", "pork", "port", "pose", "poos", "posh",
    "post", "pots", "pour", "pout", "pray", "prep", "prey", "prod", "prof",
    "prom", "prop", "pors", "prow", "pubs", "puck", "puff", "pugs", "puke",
    "pull", "pulp", "puma", "pump", "punk", "puns", "pupa", "pups", "pure",
    "purl", "purr", "push", "puss", "puts", "pyre", "pyro", "quad", "quip",
    "quit", "quiz", "race", "rack", "racy", "rads", "raft", "rage", "rags",
    "raid", "rail", "rain", "rake", "ramp", "rams", "rank", "rant", "raps",
    "rare", "rash", "rasp", "rate", "rats", "rave", "raws", "rays", "raze",
    "read", "real", "reap", "rear", "reck", "recs", "redo", "reef", "reek",
    "refs", "rein", "rely", "rend", "rent", "repo", "reps", "rest", "ribs",
    "rice", "rich", "ride", "rids", "rife", "riff", "rifs", "rift", "rigs",
    "rile", "rind", "ring", "rink", "riot", "ripe", "rise", "rise", "risk",
    "rite", "road", "roam", "roar", "robe", "robs", "rock", "rode", "rods",
    "roil", "role", "roll", "romp", "roof", "rook", "room", "root", "rope",
    "rose", "rosy", "rots", "rout", "rove", "rows", "rubs", "ruby", "ruck",
    "rude", "ruff", "ruin", "rule", "rump", "rugs", "rums", "rune", "rung",
    "runs", "runt", "ruse", "rush", "rusk", "rust", "ruth", "ruts", "rynd",
    "sack", "sacs", "safe", "saga", "sage", "sags", "said", "sail", "sake",
    "sale", "same", "salt", "sand", "sane", "sank", "sans", "sash", "save",
    "sawn", "saws", "says", "scab", "scag", "scam", "scan", "scar", "scry",
    "scud", "scum", "seal", "seam", "sear", "seat", "secs", "sect", "seed",
    "seed", "seek", "seel", "seem", "seen", "seep", "seer", "sees", "sego",
    "self", "sell", "send", "sent", "serf", "sets", "sewn", "sews", "sexy",
    "shaw", "shag", "shah", "sham", "shed", "shes", "shim", "shin", "ship",
    "shiv", "shod", "shoe", "shoo", "shop", "shot", "show", "sick", "side",
    "sift", "sigh", "sign", "silk", "sill", "silo", "silt", "sine", "sing",
    "sink", "sins", "sips", "sire", "sirs", "site", "sith", "sits", "size",
    "skat", "skew", "skid", "skim", "skin", "skip", "skis", "skit", "slag",
    "slab", "slam", "slap", "slat", "slay", "sled", "slew", "slim", "slit",
    "slip", "slit", "slob", "slog", "slop", "slot", "slow", "slug", "slum",
    "slur", "slut", "smit", "smog", "smug", "snag", "snap", "snip", "snot",
    "snow", "snub", "snug", "soak", "soap", "soar", "sobs", "sock", "soda",
    "sods", "sofa", "soft", "soil", "sold", "sole", "solo", "some", "song",
    "soon", "soot", "sore", "sort", "soul", "soup", "sour", "sows", "soys",
    "spam", "span", "spas", "spat", "spay", "spec", "sped", "spew", "spin",
    "spit", "spot", "spun", "stab", "stag", "star", "stat", "stay", "stem",
    "step", "stew", "stew", "stir", "stop", "stow", "stub", "stud", "stun",
    "subs", "such", "suck", "suds", "sued", "sues", "suit", "sulk", "sumo",
    "sums", "sung", "sunk", "suns", "sups", "sure", "surf", "swab", "swag",
    "swam", "swan", "swap", "swat", "sway", "swig", "swim", "swob", "syke",
    "sync", "tabs", "tack", "taco", "tact", "tads", "tail", "take", "talc",
    "tale", "talk", "tall", "tame", "tamp", "tang", "tank", "tans", "tape",
    "taps", "tare", "tarn", "tarp", "tart", "task", "tate", "taut", "teal",
    "taxi", "teak", "team", "tear", "teas", "tech", "teen", "tell", "temp",
    "tend", "tens", "tent", "term", "test", "text", "than", "that", "thaw",
    "them", "thaw", "thee", "then", "they", "thin", "this", "thou", "thro",
    "thru", "thud", "thug", "thus", "tick", "tics", "tide", "tidy", "tied",
    "tier", "ties", "tiff", "tile", "till", "tils", "tilt", "time", "tint",
    "tiny", "tips", "tire", "tits", "toad", "toes", "toft", "tofu", "toga",
    "toil", "toke", "told", "toll", "tomb", "tome", "tone", "tong", "tons",
    "took", "tool", "toon", "toot", "tops", "torn", "tort", "tory", "tosh",
    "toss", "tote", "tour", "tout", "town", "tows", "toys", "trap", "tray",
    "tree", "trek", "trig", "trim", "trio", "trip", "trod", "trot", "trow",
    "troy", "true", "tsar", "tuba", "tube", "tubs", "tuck", "tuft", "tugs",
    "tuna", "tune", "tuns", "turd", "turf", "turk", "turn", "tush", "tusk",
    "tuts", "twas", "twig", "twin", "twit", "twos", "type", "typo", "tzar",
    "ugly", "ukes", "umps", "undo", "unit", "unit", "unto", "undo", "upon",
    "urea", "urge", "urns", "used", "user", "uses", "vacs", "vail", "vain",
    "vamp", "vane", "vans", "vars", "vary", "vase", "vast", "vats", "veal",
    "veer", "veil", "vend", "vent", "verb", "very", "vest", "veto", "vets",
    "vial", "vibe", "vice", "vids", "view", "vile", "vine", "viny", "visa",
    "vita", "vise", "vive", "void", "volt", "vote", "vows", "wack", "wade",
    "wads", "waft", "wage", "wags", "wail", "wain", "wait", "wake", "walk",
    "wall", "wand", "wane", "wank", "want", "ward", "ware", "warm", "warn",
    "warp", "wars", "wart", "wary", "wash", "wasp", "watt", "wave", "wavy",
    "waxy", "ways", "weak", "wean", "wear", "webs", "weds", "weed", "week",
    "weep", "ween", "weld", "well", "welt", "wend", "went", "wept", "were",
    "west", "wets", "wham", "whap", "what", "when", "whew", "whey", "whig",
    "whim", "whip", "whir", "whiz", "whoa", "whom", "whop", "whys", "wick",
    "wide", "wife", "wigs", "wild", "will", "wilt", "wily", "wimp", "wind",
    "wine", "wing", "wink", "wins", "wipe", "wire", "wiry", "wise", "wish",
    "wisp", "wist", "with", "wits", "wive", "woes", "woke", "wolf", "wonk",
    "wons", "wont", "wood", "woof", "wool", "word", "woos", "wore", "work"
    "word", "worm", "worn", "wove", "wows", "wrap", "wren", "writ", "wuss",
    "yack", "yams", "yang", "yank", "yaps", "yard", "yarn", "yawl", "yawn",
    "yaws", "yays", "yeah", "yean", "year", "yell", "yelp", "yeti", "yews",
    "yipe", "yips", "yogi", "yolk", "yore", "your", "yous", "yowl", "yuca",
    "yuck", "yoga", "yurt", "yule", "zags", "zaps", "zeal", "zero", "zany",
    "zest", "zeta", "zigs", "zinc", "zing", "zips", "zits", "zone", "zonk",
    "zoom", "zoos"
};
static const string wrd5Ltr[] {"aargh", "aback", "abate", "abash", "abhor",
    "about", "above", "abort", "abyss", "abide", "acorn", "acted", "acute",
    "adopt", "adorn", "affix", "afoot", "after", "agile", "agree", "aisle",
    "alarm", "album", "alert", "alias", "alien", "align", "alive", "alloy",
    "allow", "aloft", "alone", "along", "amaze", "amber", "among", "ample",
    "amped", "angel", "angle", "anger", "angst", "annex", "anvil", "apple",
    "apply", "apron", "apsis", "aptly", "arena", "argue", "arise", "arose",
    "arson", "ashes", "askew", "asked", "asset", "atlas", "atoll", "atoms",
    "attic", "aught", "audio", "avail", "award", "awash", "awful", "awoke",
    "axial", "axiom", "aware", "backs", "baggy", "baked", "bakes", "baker",
    "balls", "balsa", "banal", "banjo", "banks", "bards", "barge", "barns",
    "basic", "bases", "baton", "batch", "bazar", "beads", "beard", "beans",
    "beats", "beast", "beach", "beefy", "beers", "began", "beget", "begin",
    "beige", "bells", "below", "belts", "bench", "belay", "bends", "beset",
    "betas", "bible", "bikes", "bills", "biome", "bison", "binge", "bites",
    "black", "blame", "bland", "blank", "blare", "birds", "blaze", "bleak",
    "blend", "bless", "blimp", "blind", "blink", "blips", "blitz", "bloat",
    "block", "blood", "blond", "blots", "blown", "blows", "blued", "blume",
    "blurt", "blunt", "blush", "board", "boast", "boils", "bolts", "bones",
    "bombs", "bonds", "bongo", "bonus", "books", "boots", "bound", "bouts",
    "bowls", "boxer", "brain", "brave", "bread", "break", "brews", "bribe",
    "brick", "bride", "bring", "brief", "brine", "broil", "broth", "broil",
    "broke", "broom", "brown", "brush", "budge", "build", "built", "bulky",
    "bulls", "bumpy", "bunch", "bunks", "buoys", "burnt", "burst", "bused",
    "buses", "bushy", "busts", "bytes", "cabal", "cabin", "cable", "cache",
    "calls", "calms", "calve", "camps", "canal", "candy", "canoe", "canon",
    "cards", "carol", "carts", "carve", "casks", "caste", "cache", "catch",
    "cause", "cease", "cells", "cents", "chain", "chair", "chalk", "chain",
    "chant", "charm", "chats", "cheap", "chasm", "cheat", "check", "cheek",
    "cheer", "chefs", "chess", "chest", "chews", "chewy", "chief", "child",
    "chill", "climb", "chime", "chimp", "china", "chips", "choir", "choke",
    "chomp", "chops", "chord", "chose", "chump", "chunk", "churl", "cigar",
    "civic", "cites", "claps", "clank", "clans", "clasp", "clash", "class",
    "claws", "clean", "clays", "clear", "click", "cliff", "climb", "cling",
    "cloak", "clonk", "clone", "cloth", "cloud", "clown", "clump", "clunk",
    "clung", "codec", "coded", "codex", "coils", "coins", "colds", "colon",
    "color", "comas", "comfy", "comic", "combo", "conic", "cooks", "costs",
    "cough", "could", "count", "court", "cover", "covet", "crabs", "crack",
    "craft", "cramp", "crank", "crash", "crate", "craze", "crazy", "creak",
    "cream", "creep", "crept", "crest", "crews", "cried", "crime", "crimp",
    "crisp", "croak", "crook", "crops", "crowd", "crown", "crows", "crude",
    "cruel", "crumb", "crush", "curse", "crypt", "cubed", "cubic", "cubit",
    "cusps", "cyber", "cynic", "czars", "daily", "daisy", "dairy", "dance",
    "dared", "darky", "darts", "dated", "datum", "dazed", "deals", "dealt",
    "death", "debit", "debts", "debug", "decaf", "decoy", "decay", "decks",
    "decal", "decor", "decry", "deems", "deers", "defer", "deify", "deity",
    "delay", "delta", "delve", "demos", "demur", "dense", "dents", "depot",
    "depth", "derby", "deter", "detox", "dials", "diced", "digit", "diets",
    "diner", "dined", "dinky", "diode", "dirty", "disco", "dingo", "discs",
    "disks", "ditch", "ditto", "ditzy", "dizzy", "dodge", "dogma", "doing",
    "donor", "dooms", "donut", "dorks", "dorms", "doses", "doubt", "dough",
    "dozed", "dozen", "draft", "drain", "drake", "drama", "drape", "drank",
    "drawl", "dread", "dream", "dress", "dried", "drink", "drips", "drive",
    "droid", "drone", "drool", "droop", "drops", "drown", "druid", "drums",
    "drunk", "dryly", "duals", "ducks", "ducts", "dudes", "duets", "dukes",
    "dully", "dumps", "dunce", "dunes", "dupes", "dusky", "dusty", "dutch",
    "dwarf", "dweeb", "dwell", "dwelt", "dying", "eagle", "eager", "eared",
    "eared", "earls", "early", "earns", "earth", "eased", "eases", "eaten",
    "ebbed", "ebony", "echos", "edged", "edges", "edict", "edify", "edits",
    "eerie", "egged", "eight", "eject", "elate", "elbow", "elder", "elect",
    "elite", "elope", "elude", "elves", "email", "ember", "enact", "enemy",
    "enjoy", "ensue", "enter", "entry", "envoy", "epics", "equip", "erase",
    "erode", "epoch", "erred", "error", "erupt", "essay", "ethic", "ethyl",
    "evade", "event", "every", "evict", "evils", "equil", "evoke", "exact",
    "exalt", "exams", "excel", "ethic", "exile", "exits", "exist", "expel",
    "extra", "exude", "extol", "exult", "euros", "eying", "fable", "faced",
    "facts", "faded", "fairy", "faith", "falls", "false", "farce", "famed",
    "fancy", "fangs", "farms", "farts", "fasts", "fatal", "fault", "favor",
    "fawns", "faxes", "fazed", "fears", "feast", "feats", "feeds", "feign",
    "fells", "felon", "felts", "fence", "fends", "feral", "ferns", "ferry",
    "fests", "fetal", "fetch", "fetid", "feuds", "fever", "fewer", "field",
    "fifer", "fiery", "fifth", "fifty", "fight", "filed", "files", "films",
    "filth", "final", "finds", "fines", "fired", "fires", "firns", "first",
    "fishy", "fists", "fixed", "fizzy", "fjord", "flack", "flags", "flail",
    "flair", "flake", "flame", "flank", "flaps", "flare", "flash", "flats",
    "fleas", "flies", "flows", "floss", "flood", "flubs", "fluid", "flunk",
    "flute", "flush", "flyby", "foams", "focus", "foils", "folds", "folly",
    "folky", "fonts", "foods", "foots", "force", "found", "fowls", "frags",
    "frail", "frame", "franc", "frays", "freak", "fresh", "forts", "fraud",
    "fries", "frisk", "frock", "front", "froth", "frost", "frown", "froze",
    "fruit", "fudge", "fuels", "fumed", "fumes", "funds", "funks", "funky",
    "furls", "fused", "fuses", "fussy", "futsy", "futon", "fuzzy", "gaffe",
    "gains", "gaits", "games", "gamma", "gangs", "gases", "gasps", "gated",
    "gates", "gaudy", "gauge", "gaunt", "gauze", "gazed", "gears", "gecko",
    "geeky", "genre", "gents", "geode", "germs", "ghast", "ghost", "ghoul",
    "giant", "gifts", "gills", "girls", "girth", "gland", "glass", "glare",
    "gleam", "glass", "glide", "glime", "glint", "gloat", "globe", "gloom",
    "glory", "gloss", "glove", "glows", "glued", "gluon", "gnarl", "gnats",
    "gnome", "goals", "goats", "godly", "going", "golds", "golfs", "goner",
    "goods", "goons", "goops", "goose", "gores", "gorge", "gouge", "gourd",
    "gowns", "grabs", "grace", "grade", "grads", "graft", "grail", "grain",
    "grams", "grand", "grant", "grape", "graph", "grasp", "grass", "grate",
    "grave", "grays", "graze", "great", "greed", "greek", "greet", "grill",
    "grime", "grind", "groan", "groin", "groom", "gross", "group", "growl",
    "grown", "grows", "grubs", "gruel", "gruff", "grump", "grunt", "guard",
    "guava", "guess", "guest", "guide", "guild", "guilt", "gulch", "gulfs",
    "gulps", "gunky", "gusts", "gusty", "gutsy", "gypsy", "gyros", "habit",
    "hacks", "haiku", "hails", "hairs", "hairy", "halos", "halts", "halve",
    "hands", "handy", "hangs", "happy", "hardy", "harps", "harsh", "haste",
    "hatch", "hated", "hater", "haunt", "havoc", "hawks", "hazed", "heads",
    "heals", "heaps", "heard", "heart", "heavy", "hedge", "heels", "hefts",
    "heirs", "heist", "helix", "hello", "helms", "helps", "hence", "herbs",
    "hertz", "hiker", "hilts", "hints", "hippo", "hippy", "hired", "hires",
    "hitch", "hoard", "hobby", "hoist", "holds", "holes", "honed", "honey",
    "honks", "honor", "hoods", "hooks", "hoped", "horde", "horns", "horse",
    "hoses", "hosts", "hotel", "hotly", "hours", "house", "hover", "howls",
    "huffs", "hulky", "human", "humid", "humor", "humps", "hunks", "hunts",
    "hurls", "hurry", "hurts", "husks", "hydra", "hydro", "hymns", "hyper",
    "icier", "icily", "icons", "ideal", "ideas", "idiom", "idiot", "idler",
    "idols", "igloo", "idyll", "image", "imply", "inane", "incur", "index",
    "inept", "inert", "infer", "ingot", "inked", "inlay", "inlet", "inned",
    "inner", "input", "inter", "intro", "ionic", "iotas", "irate", "irked",
    "irons", "irony", "isles", "islet", "issue", "itchy", "items", "ivory",
    "jails", "jarls", "jaunt", "jawed", "jeans", "jeeps", "jeers", "jello",
    "jerks", "jests", "jibed", "joins", "joint", "joist", "joked", "joust",
    "jowls", "judge", "juice", "juicy", "jukes", "jumbo", "jumps", "junks",
    "juror", "junta", "kayak", "keels", "keeps", "kempt", "khaki", "khans",
    "kicks", "kills", "kilos", "kinks", "kings", "kiosk", "kites", "knack",
    "knead", "knees", "knell", "knelt", "knife", "knits", "knobs", "knock",
    "knoll", "known", "knows", "knurl", "konks", "kudos"
}; //todo -- more 5 letter words
static const string wrd6Ltr[] = {"abated", "abject", "absent", "accord",
    "access", "accent", "aching", "acquit", "actual", "acumen", "adagio",
    "adhere", "admire", "adopts", "absorb", "adroit", "advent", "affect",
    "agreed", "airing", "albums", "aliens", "allele", "alpine", "ambers",
    "analog", "annual", "anoint", "anvils", "appear", "armpit", "artist",
    "asleep", "assert", "assign", "aspect", "assort", "atomic", "atolls",
    "attend", "attest", "audits", "avatar", "awaken", "babble", "babied",
    "badger", "bakery", "baller", "ballet", "banged", "banned", "barely",
    "basalt", "basket", "battle", "beacon", "beards", "became", "become",
    "beelte", "behind", "behold", "behest", "beings", "bellow", "benign",
    "beside", "bestow", "betray", "beware", "beyond", "biceps", "bikini",
    "biomes", "biopsy", "blanks", "blasts", "blower", "blurbs", "boiled",
    "booger", "border", "botany", "bottom", "bounce", "boyish", "brawls",
    "breach", "bribed", "breath", "bridge", "bridle", "bright", "brunch",
    "browse", "brutes", "bubble", "bucket", "budget", "bulked", "bummer",
    "bumped", "bundle", "bunker", "buoyed", "bursts", "busted", "buzzer",
    "bygone", "cackle", "cabins", "calves", "campus", "candid", "cannon",
    "canyon", "carbon", "cardio", "caring", "cartel", "cashew", "casino",
    "catchy", "ceased", "cellar", "census", "chains", "chairs", "champs",
    "charts", "checks", "cheers", "chests", "choirs", "chords", "chrome",
    "circus", "citrus", "cities", "citrus", "civics", "clench", "clergy",
    "clicks", "climax", "cloaks", "clones", "closer", "closed", "closet",
    "cloudy", "clumps", "coated", "coerce", "coffee", "cohort", "coiled",
    "coldly", "colony", "column", "commit", "comply", "concur", "corona",
    "cortex", "costal", "cotton", "coupon", "course", "coughs", "cousin",
    "coward", "cowboy", "courts", "coyote", "crabby", "cracks", "cranky",
    "crayon", "crease", "creeks", "crests", "crises", "critic", "crooks",
    "crouch", "crowds", "cruise", "crutch", "cuddle", "cupola", "curate",
    "curfew", "cursed", "custom", "cutoff", "cyborg", "cycler", "cycles",
    "cymbal", "cypher", "cynics", "dabble", "dangle", "danger", "dancer",
    "puzzle", "letter", "evolve", "expand", "export",
}; //todo -- More 6 letter words
static const string wrd7Ltr[] = {"abandon", "abashes", "abashed", "abetter",
    "abolish", "abscond", "abusive", "acceded", "acclaim", "accusal",
    "account", "accuses", "acidity", "acrobat", "acronym", "acrylic",
    "actress", "acutely", "adamant", "adapted", "addicts", "address",
    "adeptly", "adhered", "adjoint", "admires", "advance", "affirms",
    "against", "allergy", "almonds", "already", "ammonia", "ampules",
    "amulets", "amusers", "analogs", "anaemic", "analyze", "anchovy",
    "apostle", "applets", "arousal", "arrests", "arrival", "arsenal",
    "artwork", "ascends", "asphalt", "assumed", "assured", "astound",
    "atomize", "attains", "attract", "auction", "augment", "authors",
    "avatars", "avenues", "avocado", "awesome", "azimuth", "baboons",
    "backing", "baffled", "baggers", "bailout", "bailiff", "balding",
    "ballads", "bandage", "bankers", "banking", "banters", "barrage",
    "barrier", "bashful", "basking", "bastion", "batched", "bathing",
    "battery", "bayonet", "bazooka", "beached", "beacons", "beaming",
    "bearded", "beastly", "beating", "beavers", "because", "becloak",
    "bedrock", "believe", "benefit", "berated", "berserk", "besides",
    "biaxial", "biology", "bismuth", "bitmaps", "bitting", "blacken",
    "bladder", "blaming", "blasted", "bleakly", "blender", "blinded",
    "blocked", "blossom", "blunder", "boarded", "boiling", "boldest",
    "bolting", "bonanza", "bonkers", "booklet", "boosted", "booming",
    "bootleg", "boredom", "bottled", "boulder", "bounced", "boycott",
    "brabble", "bracket", "bragged", "braided", "bramble", "branchy",
    "bravado", "bravery", "breaded", "breathe", "breeder", "brewing",
    "bribery", "briefed", "bringer", "bristle", "broadly", "brother",
    "buffalo", "buildup", "bunched", "burglar", "burning", "burrito",
    "bursted", "butcher", "cabbage", "caboose", "cadence", "cadaver",
    "calling", "calvary", "capable", "ceiling", "certain", "cheddar",
    "choking", "cistern", "circuit", "citizen", "claimed", "clasped",
    "classic", "cleaned", "cleanse", "cleanly", "cleared", "cleaver",
    "climate", "closest", "clutter", "coerced", "coheres", "coldest",
    "commits", "commute", "compile", "compete", "concoct", "confirm",
    "congest", "conflux", "console", "convert", "convene", "cookies",
    "cricket", "crossed", "cryptic", "cumquat", "cushion", "cynical",
    "cyclone", "daytime", "decades", "decayed", "decency", "decided",
    "declare", "decrypt", "decuple", "deduced", "deducts", "defeats",
    "defense", "deficit", "defined", "deflate", "deflect", "defrost",
    "defunct", "degrees", "deleted", "delight", "delving", "departs",
    "deposit", "deprave", "depress", "deploys", "descent", "dessert",
    "destain", "despair", "details", "detains", "destiny", "detects",
    "devalue", "devisor", "devoted", "diagram", "diamond", "diaries",
    "diaster", "digital", "dilemma", "dingbat", "diorama", "disable",
    "disgust", "disjoin", "disobey", "dispart", "display", "disrupt",
    "distant", "distort", "distill", "disturb", "diverse", "divulge",
    "divvied", "doorway", "dossier", "drastic", "drizzle", "droplet",
    "drywall", "ductile", "duelist", "dullest", "durable", "dutiful",
    "dynasty", "dynamos", "earlier", "earmark", "earning", "easiest",
    "emblaze", "empress", "endless", "endorse", "endured", "enliven",
    "ensnare", "enquiry", "entrain", "envelop", "entrust", "epigram",
    "epsilon", "equally", "erosion", "etching", "evasion", "exclaim",
    "execute", "exerted", "exhaled", "exhibit", "existed", "expands",
    "expense", "explain", "exploit", "exports", "express", "extends",
    "extinct", "extract", "extrude", "extreme", "eyebrow", "eyewear",
    "factory", "factual", "factors", "faculty", "failure",
    "cuisine", "letters", "balloon" }; // todo -- add more 7 letter words
static const string wrd8Ltr[] = {"aardvark", "abatable", "abidance", "abnormal",
    "abrasion", "abrasive", "abruptly", "absolute", "academia", "accepted",
    "accessed", "accident", "acclaims", "accorded", "accounts", "accredit",
    "accuracy", "accusers", "accustom", "acescent", "achieved", "adorable",
    "adverted", "advocacy", "advocate", "allegory", "allergen", "alliance",
    "alliance", "allocate", "allotted", "allowing", "alluding", "allusion",
    "alternat", "alpinist", "altitude", "although", "amateurs", "ambience",
    "amenable", "amethyst", "amortize", "aneurism", "annoying", "annulled",
    "anointed", "anthills", "approach", "approval", "appraise", "applause",
    "appendix", "aquatics", "aromatic", "arpeggio", "arrested", "artifact",
    "artistic", "arythmic", "ascetics", "ascribed", "assailed", "assaults",
    "assassin", "asserted", "assorted", "assuming", "asterisk", "astonish",
    "astricts", "athletes", "atomical", "atoricty", "autonomy", "autumnal",
    "backside", "backward", "bacteria", "baguette", "bailiffs", "balanced",
    "balloons", "balsamic", "bankrupt", "banquets", "barbaric", "barbeque",
    "basilisk", "basilica", "basement", "basaltic", "barracks", "basaltic",
    "barriers", "basement", "beckoned", "befooled", "befitted", "bedstand",
    "befriend", "befuddle", "begotten", "behavior", "behemoth", "belaying",
    "believed", "belittle", "bellowed", "belonged", "bemoaned", "bemuddle",
    "bemusing", "bendable", "bewilder", "biologic", "binomial", "blizzard",
    "boasting", "bluffing", "bludgeon", "brambles", "branched", "brutally",
    "brouhaha", "brothers", "broccoli", "brunette", "buoyancy", "burdened",
    "burglary", "burnable", "burrowed", "bursting", "business", "buzzards",
    "buzzword", "calamity", "caffeine", "cakewalk", "calamari", "capsized",
    "captains", "captions", "captives", "captured", "cardigan", "cardioid",
    "careless", "casement", "cashiers", "cassette", "casualty", "casually",
    "catalogs", "catalyst", "catacomb", "catapult", "category", "causeway",
    "cavalier", "caverned", "cavefish", "celibacy", "cellular", "cemetary",
    "censored", "centaurs", "centered", "centrals", "centrist", "centriod",
    "cerebral", "ceremony", "chemical", "cheetahs", "cheerful", "cheating",
    "chaffeur", "cheekily", "chiefdom", "chipmonk", "chipotle", "chiseled",
    "children", "childish", "chewable", "chestnut", "citizens", "citation",
    "citadels", "circular", "cisterns", "cinnamon", 
    "icecream"}; // todo -- add more 8 letter words
static const string wrd9Ltr[] = {"astronaut", "adaptable", "abundance",
    "circuitry", "jubilance", "volcanize", "hypnotize", "haphazard",
    "frequence", "emphasize", "equipment", "formalize",
    "sequences"}; //todo -- add more 9 letter words
static const string wrd10Ltr[] = {"abdication", "abhorrence", "abjectness",
    "abnormally", "abolitions", "aboveboard", "abridgment", "abruptness",
    "absolutely", "absolutism", "absorption", "abstaining", "absitnence",
    "abundances", "academical", "accelerant", "accentless", "accelerate",
    "activeness", "actualized", "aeronautic", "aesthetics", "affidavits",
    "affectless", "affiliates", "affinities", "affirmance", "affixation",
    "affliction", "affluences", "affordable", "aficionado", "afterwords",
    "aggravated", "aggression", "aggrements", "alarmingly", "allegation",
    "allegorize", "allergenic", "alleviants", "allusively", "allotropic",
    "allurement", "alongshore", "alphabetic", "alternates", "alternator",
    "altogether", "amalgamate", "ambassador", "ambivalent", "ammunition",
    "amorphisms", "ampersands", "amphibious", "amplitudes", "amusements",
    "analytical", "analyzable", "anarchists", "anatomical", "anemically",
    "anesthesia", "anesthetic", "annihilate", "annotating", "announcers",
    "annoyingly", "anointment", "answerable", "antagonize", "antebellum",
    "antecedent", "anthropoid", "antibiotic", "antiquated", "antisocial",
    "antithesis", "apartments", "apocalypse", "apolitical", "apologetic",
    "apologises", "apparently", "apparition", "appearance", "appeasable",
    "appendages", "appertains", "appetizers", "applauding", "aristocrat",
    "applesauce", "appointees", "applicants", "apposition", "appraisals",
    "appreicate", "apprehends", "apprentice", "approvable", "archeology",
    "archetypes", "articulate", "ascendance", "ascendancy", "ascertains",
    "aspherical", "aspirating", "aspiration", "assailable", "assailants",
    "assemblage", "assemblers", "assessable", "assessment", "assoiciate",
    "assortment", "assumption", "assurances", "asteroidal", "astonished",
    "astounding", "astringent", "astrologer", "astronomer", "astuteness",
    "asymmetric", "asymptotic", "asynchrony", "atmosphere", "attachable",
    "attainable", "attendance", "attenuated", "attestants", "attractant",
    "attraction", "atypically", "auctioneer", "averseness", "avoidances",
    "awakenings", "avocations", "background",
    "jackhammar", "programing"};//todo -- more 10 letter words
static const string wrd11Ltr[] = {"abandonment", "abbreviated", "abnormality",
    "abolishable", "abolishment", "abomination", "aboveground", "accelerator",
    "acceptances", /*          */ "accessorize", "accidentals", "acclimation",
    "acclimatize", "accommodate", "accomplices", "accordingly", "accountable",
    "achievement", "acknowledge", "acquirement", "acquisition", "acrimoniois",
    "activations", "actualities", "acupuncture", "adaptations", "addressable",
    "adjacencies", "adjustments", "adolescence", "advancement", "adverseness",
    "affectional", "affectively", "afficionado", "affiliation", "affirmation",
    "affirmative", "agglomerate", "agelessness", "aggrandized", "aggravating",
    "aimlessness",
    "fabrication", "overcomplex"}; //todo... moar words 11 lettrs 
static const string wrd12Ltr[] = {"extravaganza", "embezzlement",
    "equalization", "maximization", "unquenchable", "inexplicably",
    "fabrications", "quantization", "inexplicable", "colloquially",
    "preoccupancy", "equivalently", "majestically",
}; //more words here too

//--------------------------------------------------------------------
//  Function Prototypes
//--------------------------------------------------------------------
void printWelcome(void);
void printFarewell(int correct, int incorrect);
int getUserInputInt(string&);
void clearInputStream(void);
//void doUserGuess(SequenceEnum&, int&, int&); //Object slicing ruined my day
void doUserGuess(SequenceEnum*, int&, int&); //Luckily, pointers to the rescue
void countWordsOfEachLength(int *);


//--------------------------------------------------------------------
//  main
//--------------------------------------------------------------------
int main(int argc, const char * argv[]) {
    //Variables for main()
    float percentCorrect = 0.0;
    bool keepPlaying = true;
    int correctGuesses = 0;
    int incorrectGuesses = 0;
    int substrLength = 0; //Used in seqExtract
    int substrStartIndex = 0; //Used in seqExtract
    int sequenceEnumToDo;
    int userInputInt; //User input when user input is an integer
    int randomWordInVector;
    //string userInputStr;
    int numWordsOfEachLength [MAX_PREDEFINED_WORD_LENGTH];
    string userPromptForWordLength = "Enter number of letters for guessWord"
    " [3 - 12, or 0 to quit]:";
    
    //------------------------------------------------------------------------
    //Initialization Routines
    //------------------------------------------------------------------------
    //Set Random Seed
    srand((uint)time(NULL));
    
    //Figure out how many words of each length there are to choose from
    countWordsOfEachLength(numWordsOfEachLength);
    //This next bit of logic may seem confusing, if I was allowed to use integer
    //literals instead of hiding them behind constants for word index values
    //that will NEVER change, it probably would be easier to follow. Oh well...
    
    //Generate a large collection of sequenceEnum objects for each word lengths
    //I used 'rand() % 3' to decide which type of object to construct for each
    //word. I construct all the objects up front during initialization
    std::vector<SequenceEnum *> wordHolder3Ltr; //word holder for 3-letter words
    for (string s : wrd3Ltr) { //For each string in wrd3Ltr
        sequenceEnumToDo = rand() % SEQ_ENUM_VARIANTS; //3 variants currently
        if (DO_SEQ_ENUM == sequenceEnumToDo) {
            //Vector will keep ref to heap memory, I will delete during cleanup
            SequenceEnum * temp = new SequenceEnum(s);
            wordHolder3Ltr.push_back(temp); //Do sequence Enum
        }
        else if (DO_SEQ_EXTRACT == sequenceEnumToDo) {
            //Need to compute a sequence extract string. here it is easy, since
            string substr = ""; //For 3 letter words, only extract middle letter
            substr += s.at(SECND_LTR_OF_WRD_INDX);
            SeqExtract * temp = new SeqExtract(s, substr); //Construct object
            wordHolder3Ltr.push_back( temp);
        }
        else { //if (DO_SPAS_ENUM == sequenceEnumToDo)
            SpasEnum * temp = new SpasEnum(s);
            wordHolder3Ltr.push_back(temp); //do SpasEnum
        }
    }
    std::vector<SequenceEnum *> wordHolder4Ltr; //word holder for 4 letter words
    for (string s : wrd4Ltr) {
        sequenceEnumToDo = rand() % SEQ_ENUM_VARIANTS;
        if (DO_SEQ_ENUM == sequenceEnumToDo) {
            SequenceEnum * temp = new SequenceEnum(s);
            wordHolder4Ltr.push_back(temp); //Do sequence Enum
        }
        else if (DO_SEQ_EXTRACT == sequenceEnumToDo) {
            string substr;
            substrStartIndex = (rand() % (FOUR_LETTERS - SECND_LTR_OF_WRD_INDX))
            + SECND_LTR_OF_WRD_INDX; //(rand() % (4-1)) + 1    will equal 1 or 2
            if (substrStartIndex > SECND_LTR_OF_WRD_INDX) {
                substrLength = SECND_LTR_OF_WRD_INDX; //aka substrLength = 1
            }
            else {
                substrLength = rand() % SECND_LTR_OF_WRD_INDX;
            }
            substr = s.substr(substrStartIndex, substrLength);
            SeqExtract * temp = new SeqExtract(s, substr);
            wordHolder4Ltr.push_back(temp);
        }
        else { //if DO_SPAS_ENUM == sequenceEnumToDo
            SpasEnum * temp = new SpasEnum(s);
            wordHolder4Ltr.push_back(temp); //Do sequence Enum
        }
    }
    std::vector<SequenceEnum *> wordHolder5Ltr; //Create vec for 5 letter words
    for (string s : wrd5Ltr) {
        sequenceEnumToDo = rand() % SEQ_ENUM_VARIANTS;
        if (DO_SEQ_ENUM == sequenceEnumToDo) {
            SequenceEnum * temp = new SequenceEnum(s);
            wordHolder5Ltr.push_back(temp); //Do sequence Enum
        }
        else if (DO_SEQ_EXTRACT == sequenceEnumToDo) {
            string substr;
            substrStartIndex = (rand() % (FIVE_LETTERS - SECND_LTR_OF_WRD_INDX))
            + SECND_LTR_OF_WRD_INDX; //(rand() % (5-1)) + 1
            if (substrStartIndex > SECND_LTR_OF_WRD_INDX) {
                substrLength = (rand() % SECND_LTR_OF_WRD_INDX) +
                SECND_LTR_OF_WRD_INDX; //1 or 2
                //Need to make sure substrLength isn't too long though
                if (substrLength + substrStartIndex > FIVE_LETTERS) {
                    substrLength = FIVE_LETTERS - substrStartIndex;
                }
            }
            else {
                substrLength = (rand() % THREE_LETTERS) + SECND_LTR_OF_WRD_INDX;
            }
            substr = s.substr(substrStartIndex, substrLength);
            SeqExtract * temp = new SeqExtract(s, substr);
            wordHolder5Ltr.push_back(temp);
        }
        else { //if DO_SPAS_ENUM == sequenceEnumToDo
            SpasEnum* temp = new SpasEnum(s);
            wordHolder5Ltr.push_back(temp);
        }
    }
    std::vector<SequenceEnum *> wordHolder6Ltr; //6 letter words
    for (string s : wrd6Ltr) {
        sequenceEnumToDo = rand() % SEQ_ENUM_VARIANTS;
        if (DO_SEQ_ENUM == sequenceEnumToDo) {
            SequenceEnum * temp = new SequenceEnum(s);
            wordHolder6Ltr.push_back(temp); //Do sequence Enum
        }
        else if (DO_SEQ_EXTRACT == sequenceEnumToDo) {
            //Gotta figure out a substring from the word to have removed
            string substr;
            //Calculate substring start index
            substrStartIndex = (rand() % (SIX_LETTERS - SECND_LTR_OF_WRD_INDX))
            + SECND_LTR_OF_WRD_INDX; //(rand() % (6-1)) + 1
            //Calculate substring length based off of word length and start indx
            if (substrStartIndex > SECND_LTR_OF_WRD_INDX) {
                substrLength = rand() % (SIX_LETTERS - SECND_LTR_OF_WRD_INDX -
                                         (FIVE_LETTERS - substrStartIndex)) +
                SECND_LTR_OF_WRD_INDX;
                //Need to make sure substrLength isn't too long
                if ( (substrLength + substrStartIndex) > SIX_LETTERS) {
                    substrLength = SIX_LETTERS - substrStartIndex;
                }
            }
            else {
                substrLength = (rand() % FOUR_LETTERS) + SECND_LTR_OF_WRD_INDX;
            }
            substr = s.substr(substrStartIndex, substrLength); //Get substring
            SeqExtract * temp = new SeqExtract(s, substr);
            wordHolder6Ltr.push_back(temp);
        }
        else { //if DO_SPAS_ENUM == sequenceEnumToDo
            SpasEnum * temp = new SpasEnum(s);
            wordHolder6Ltr.push_back(temp);
        }
    }
    std::vector<SequenceEnum *> wordHolder7Ltr;
    for (string s : wrd7Ltr) {
        sequenceEnumToDo = rand() % SEQ_ENUM_VARIANTS;
        if (DO_SEQ_ENUM == sequenceEnumToDo) {
            SequenceEnum * temp = new SequenceEnum(s);
            wordHolder7Ltr.push_back(temp); //Do sequence Enum
        }
        else if (DO_SEQ_EXTRACT == sequenceEnumToDo) {
            //Gotta figure out a substring from the word to have removed
            string substr;
            //Calculate substring start index
            substrStartIndex = (rand() %(SEVEN_LETTERS - SECND_LTR_OF_WRD_INDX))
            + SECND_LTR_OF_WRD_INDX; //(rand() % (7-1)) + 1
            //Calculate substring length based off of word length and start indx
            if (substrStartIndex > SECND_LTR_OF_WRD_INDX) {
                substrLength = (rand() % THREE_LETTERS) + SECND_LTR_OF_WRD_INDX;
                //Need to make sure substrLength isn't too long
                if ( (substrLength + substrStartIndex) > SEVEN_LETTERS) {
                    substrLength = SEVEN_LETTERS - substrStartIndex;
                }
            }
            else {
                substrLength = (rand() % FOUR_LETTERS) + SECND_LTR_OF_WRD_INDX;
            }
            substr = s.substr(substrStartIndex, substrLength); //Get substring
            SeqExtract * temp = new SeqExtract(s, substr);
            wordHolder7Ltr.push_back(temp);
        }
        else { //if DO_SPAS_ENUM == sequenceEnumToDo
            SpasEnum * temp = new SpasEnum(s);
            wordHolder7Ltr.push_back(temp);
        }
    }
    std::vector<SequenceEnum *> wordHolder8Ltr;
    for (string s : wrd8Ltr) {
        sequenceEnumToDo = rand() % SEQ_ENUM_VARIANTS;
        if (DO_SEQ_ENUM == sequenceEnumToDo) {
            SequenceEnum * temp = new SequenceEnum(s);
            wordHolder8Ltr.push_back(temp); //Do sequence Enum
        }
        else if (DO_SEQ_EXTRACT == sequenceEnumToDo) {
            //Gotta figure out a substring from the word to have removed
            string substr;
            //Calculate substring start index
            substrStartIndex = (rand() %(EIGHT_LETTERS - SECND_LTR_OF_WRD_INDX))
            + SECND_LTR_OF_WRD_INDX; //(rand() % (8-1)) + 1
            //Calculate substring length based off of word length and start indx
            if (substrStartIndex > SECND_LTR_OF_WRD_INDX) {
                substrLength = (rand() % THREE_LETTERS) + SECND_LTR_OF_WRD_INDX;
                //Need to make sure substrLength isn't too long
                if ( (substrLength + substrStartIndex) > EIGHT_LETTERS) {
                    substrLength = EIGHT_LETTERS - substrStartIndex; //8 - start
                }
            }
            else {
                substrLength = (rand() % FOUR_LETTERS) + SECND_LTR_OF_WRD_INDX;
            }
            substr = s.substr(substrStartIndex, substrLength); //Get substring
            SeqExtract * temp = new SeqExtract(s, substr);
            wordHolder8Ltr.push_back(temp);
        }
        else { //if DO_SPAS_ENUM == sequenceEnumToDo
            SpasEnum * temp = new SpasEnum(s);
            wordHolder8Ltr.push_back(temp);
        }
    }
    std::vector<SequenceEnum *> wordHolder9Ltr;
    for (string s : wrd9Ltr) { //Range based for loops are very handy
        sequenceEnumToDo = rand() % SEQ_ENUM_VARIANTS;
        if (DO_SEQ_ENUM == sequenceEnumToDo) {
            SequenceEnum * temp = new SequenceEnum(s);
            wordHolder9Ltr.push_back(temp); //Do sequence Enum
        }
        else if (DO_SEQ_EXTRACT == sequenceEnumToDo) {
            //Gotta figure out a substring from the word to have removed
            string substr;
            //Calculate substring start index
            substrStartIndex = (rand() %(NINE_LETTERS - SECND_LTR_OF_WRD_INDX))
            + SECND_LTR_OF_WRD_INDX; //(rand() % (9 - 1)) + 1
            //Calculate substring length based off of word length and start indx
            if (substrStartIndex > SECND_LTR_OF_WRD_INDX) {
                substrLength = (rand() % THREE_LETTERS) + SECND_LTR_OF_WRD_INDX;
                //Need to make sure substrLength isn't too long
                if ( (substrLength + substrStartIndex) > NINE_LETTERS) {
                    substrLength = NINE_LETTERS - substrStartIndex; //9 - start
                }
            }
            else { //I am keeping the length low here so that the words are not
                //   impossible to guess
                substrLength = (rand() % FIVE_LETTERS) + SECND_LTR_OF_WRD_INDX;
            }
            substr = s.substr(substrStartIndex, substrLength); //Get substring
            SeqExtract * temp = new SeqExtract(s, substr);
            wordHolder9Ltr.push_back(temp);
        }
        else { //if DO_SPAS_ENUM == sequenceEnumToDo
            SpasEnum * temp = new SpasEnum(s);
            wordHolder9Ltr.push_back(temp);
        }
    }
    std::vector<SequenceEnum *> wordHolder10Ltr;
    for (string s : wrd10Ltr) {
        sequenceEnumToDo = rand() % SEQ_ENUM_VARIANTS;
        if (DO_SEQ_ENUM == sequenceEnumToDo) {
            SequenceEnum * temp = new SequenceEnum(s);
            wordHolder10Ltr.push_back(temp); //Do sequence Enum
        }
        else if (DO_SEQ_EXTRACT == sequenceEnumToDo) {
            //Gotta figure out a substring from the word to have removed
            string substr;
            //Calculate substring start index
            substrStartIndex = (rand() %(TEN_LETTERS - SECND_LTR_OF_WRD_INDX))
            + SECND_LTR_OF_WRD_INDX; //(rand() % (10 - 1)) + 1
            //Calculate substring length based off of word length and start indx
            if (substrStartIndex > SECND_LTR_OF_WRD_INDX) {
                substrLength = (rand() % THREE_LETTERS) + SECND_LTR_OF_WRD_INDX;
                //Need to make sure substrLength isn't too long
                if ( (substrLength + substrStartIndex) > TEN_LETTERS) {
                    substrLength = TEN_LETTERS - substrStartIndex; //10 - start
                }
            }
            else { //I am keeping the length low here so that the words are not
                //   impossible to guess
                substrLength = (rand() % FIVE_LETTERS) + SECND_LTR_OF_WRD_INDX;
            }
            substr = s.substr(substrStartIndex, substrLength); //Get substring
            SeqExtract * temp = new SeqExtract(s, substr);
            wordHolder10Ltr.push_back(temp);
        }
        else { //if DO_SPAS_ENUM == sequenceEnumToDo
            SpasEnum * temp = new SpasEnum(s);
            wordHolder10Ltr.push_back(temp);
        }
    }
    std::vector<SequenceEnum *> wordHolder11Ltr;
    for (string s : wrd11Ltr) {
        sequenceEnumToDo = rand() % SEQ_ENUM_VARIANTS;
        if (DO_SEQ_ENUM == sequenceEnumToDo) {
            SequenceEnum * temp = new SequenceEnum(s);
            wordHolder11Ltr.push_back(temp); //Do sequence Enum
        }
        else if (DO_SEQ_EXTRACT == sequenceEnumToDo) {
            //Gotta figure out a substring from the word to have removed
            string substr;
            //Calculate substring start index
            substrStartIndex = (rand()%(ELEVEN_LETTERS - SECND_LTR_OF_WRD_INDX))
            + SECND_LTR_OF_WRD_INDX; //(rand() % (11 - 1)) + 1
            //Calculate substring length based off of word length and start indx
            if (substrStartIndex > SECND_LTR_OF_WRD_INDX) {
                substrLength = (rand() % THREE_LETTERS) + SECND_LTR_OF_WRD_INDX;
                //Need to make sure substrLength isn't too long
                if ( (substrLength + substrStartIndex) > ELEVEN_LETTERS) {
                    substrLength = ELEVEN_LETTERS - substrStartIndex;//11-start
                }
            }
            else { //I am keeping the length low here so that the words are not
                //   impossible to guess
                substrLength = (rand() % FIVE_LETTERS) + SECND_LTR_OF_WRD_INDX;
            }
            substr = s.substr(substrStartIndex, substrLength); //Get substring
            SeqExtract * temp = new SeqExtract(s, substr);
            wordHolder11Ltr.push_back(temp);
        }
        else { //if DO_SPAS_ENUM == sequenceEnumToDo
            SpasEnum * temp = new SpasEnum(s);
            wordHolder11Ltr.push_back(temp);
        }
    }
    std::vector<SequenceEnum *> wordHolder12Ltr;
    for (string s : wrd12Ltr) {
        sequenceEnumToDo = rand() % SEQ_ENUM_VARIANTS;
        if (DO_SEQ_ENUM == sequenceEnumToDo) {
            SequenceEnum * temp = new SequenceEnum(s);
            wordHolder12Ltr.push_back(temp); //Do sequence Enum
        }
        else if (DO_SEQ_EXTRACT == sequenceEnumToDo) {
            //Gotta figure out a substring from the word to have removed
            string substr;
            //Calculate substring start index
            substrStartIndex = (rand() %(TWELVE_LETTERS -SECND_LTR_OF_WRD_INDX))
            + SECND_LTR_OF_WRD_INDX; //(rand() % (12 - 1)) + 1
            //Calculate substring length based off of word length and start indx
            if (substrStartIndex > SECND_LTR_OF_WRD_INDX) {
                substrLength = (rand() % THREE_LETTERS) + SECND_LTR_OF_WRD_INDX;
                //Need to make sure substrLength isn't too long
                if ( (substrLength + substrStartIndex) > TWELVE_LETTERS) {
                    substrLength = TWELVE_LETTERS - substrStartIndex;//12-start
                }
            }
            else { //I am keeping the length low here so that the words are not
                //   impossible to guess
                substrLength = (rand() % FIVE_LETTERS) + SECND_LTR_OF_WRD_INDX;
            }
            substr = s.substr(substrStartIndex, substrLength); //Get substring
            SeqExtract * temp = new SeqExtract(s, substr);
            wordHolder12Ltr.push_back(temp);
        }
        else { //if DO_SPAS_ENUM == sequenceEnumToDo
            SpasEnum * temp = new SpasEnum(s);
            wordHolder12Ltr.push_back(temp);
        }
    }
    
    //-------------------------------------------------------------------
    //Start
    //-------------------------------------------------------------------
    printWelcome();
    //Game loop
    while (keepPlaying) {
        userInputInt = getUserInputInt(userPromptForWordLength);
        if (0 == userInputInt) {
            break;
        }
        else if (THREE_LETTERS == userInputInt) {
            randomWordInVector = rand() % numWordsOfEachLength[THREE_LETTERS];
           
                doUserGuess(wordHolder3Ltr.at(randomWordInVector),
                            correctGuesses, incorrectGuesses);
        }
        else if (FOUR_LETTERS == userInputInt) {
            randomWordInVector = rand() % numWordsOfEachLength[FOUR_LETTERS];
            doUserGuess(wordHolder4Ltr.at(randomWordInVector), correctGuesses,
                        incorrectGuesses);
        }
        else if (FIVE_LETTERS == userInputInt) {
            randomWordInVector = rand() % numWordsOfEachLength[FIVE_LETTERS];
            doUserGuess(wordHolder5Ltr.at(randomWordInVector), correctGuesses,
                        incorrectGuesses);
        }
        else if (SIX_LETTERS == userInputInt) {
            randomWordInVector = rand() % numWordsOfEachLength[SIX_LETTERS];
            doUserGuess(wordHolder6Ltr.at(randomWordInVector), correctGuesses,
                        incorrectGuesses);
        }
        else if (SEVEN_LETTERS == userInputInt) {
            randomWordInVector = rand() % numWordsOfEachLength[SEVEN_LETTERS];
            doUserGuess(wordHolder7Ltr.at(randomWordInVector), correctGuesses,
                        incorrectGuesses);
        }
        else if (EIGHT_LETTERS == userInputInt) {
            randomWordInVector = rand() % numWordsOfEachLength[EIGHT_LETTERS];
            doUserGuess(wordHolder8Ltr.at(randomWordInVector), correctGuesses,
                        incorrectGuesses);
        }
        else if (NINE_LETTERS == userInputInt) {
            randomWordInVector = rand() % numWordsOfEachLength[NINE_LETTERS];
            doUserGuess(wordHolder9Ltr.at(randomWordInVector), correctGuesses,
                        incorrectGuesses);
        }
        else if (TEN_LETTERS == userInputInt) {
            randomWordInVector = rand() % numWordsOfEachLength[TEN_LETTERS];
            doUserGuess(wordHolder10Ltr.at(randomWordInVector), correctGuesses,
                        incorrectGuesses);
        }
        else if (ELEVEN_LETTERS == userInputInt) {
            randomWordInVector = rand() % numWordsOfEachLength[ELEVEN_LETTERS];
            doUserGuess(wordHolder11Ltr.at(randomWordInVector), correctGuesses,
                        incorrectGuesses);
        }
        else { //if (TWELVE_LETTERS == userInputInt)
            randomWordInVector = rand() % numWordsOfEachLength[TWELVE_LETTERS];
            doUserGuess(wordHolder12Ltr.at(randomWordInVector), correctGuesses,
                        incorrectGuesses);
        }
        percentCorrect = ((float) correctGuesses /
                          (float) (incorrectGuesses + correctGuesses)) *
        ONE_HUNDRED_PERCENT;
        
        cout << "\nScore so far:\nCorrect: " << correctGuesses;
        cout << "\nIncorrect: " << incorrectGuesses;
        cout << "\nTotal Guesses: " << incorrectGuesses + correctGuesses;
        cout << "\nGuess Percentage: " << percentCorrect << "%" << std::endl;
    }
    printFarewell(correctGuesses, incorrectGuesses);
    
    //-------------------------------------------------------------------
    // Clean-Up (DELETE ALL HEAP MEMORY ALLOCATED WITH 'NEW')
    //-------------------------------------------------------------------
    for (std::vector<SequenceEnum *>::iterator it = wordHolder3Ltr.begin();
         it != wordHolder3Ltr.end(); ++it) {
        delete *it;
    }
    for (std::vector<SequenceEnum *>::iterator it = wordHolder4Ltr.begin();
         it != wordHolder4Ltr.end(); ++it) {
        delete *it;
    }
    for (std::vector<SequenceEnum *>::iterator it = wordHolder5Ltr.begin();
         it != wordHolder5Ltr.end(); ++it) {
        delete *it;
    }
    for (std::vector<SequenceEnum *>::iterator it = wordHolder6Ltr.begin();
         it != wordHolder6Ltr.end(); ++it) {
        delete *it;
    }
    for (std::vector<SequenceEnum *>::iterator it = wordHolder7Ltr.begin();
         it != wordHolder7Ltr.end(); ++it) {
        delete *it;
    }
    for (std::vector<SequenceEnum *>::iterator it = wordHolder8Ltr.begin();
         it != wordHolder8Ltr.end(); ++it) {
        delete *it;
    }
    for (std::vector<SequenceEnum *>::iterator it = wordHolder9Ltr.begin();
         it != wordHolder9Ltr.end(); ++it) {
        delete *it;
    }
    for (std::vector<SequenceEnum *>::iterator it = wordHolder10Ltr.begin();
         it != wordHolder10Ltr.end(); ++it) {
        delete *it;
    }
    for (std::vector<SequenceEnum *>::iterator it = wordHolder11Ltr.begin();
         it != wordHolder11Ltr.end(); ++it) {
        delete *it;
    }
    for (std::vector<SequenceEnum *>::iterator it = wordHolder12Ltr.begin();
          it != wordHolder12Ltr.end(); ++it) {
        delete *it;
    }
    return EXIT_SUCCESS;
}

int getUserInputInt(string& prompt) {
    bool invalidInput;
    int inputInt = 0;
    do { //Keep asking for input until valid input is given
        cout << prompt << std::endl;
        std::cin >> std::ws;  // eat up any leading white spaces
        int usrInput = std::cin.peek();  // peek character
        if ( std::isdigit(usrInput) ) {
            std::cin >> inputInt;
            //Now check to see if inputInt is in the correct range
            if( (inputInt < MAX_PREDEFINED_WORD_LENGTH &&
                 inputInt >= THREE_LETTERS) || 0 == inputInt) {
                invalidInput = false;
            }
            else {
                cout << "\nError, the number you entered is " << inputInt;
                cout << " which is outside the range ";
                cout << THREE_LETTERS << " to " << TWELVE_LETTERS;
                cout << std::endl << "Please try again\n";
                invalidInput = true;
            }
        }
        else { //If user did not enter an integer
            string badInput;
            std::cin >> badInput;
            cout << "\nError, Invalid Input. You entered: " << badInput << '\n';
            cout << std::endl << "Please try again\n";
            invalidInput = true;
        }
    } while (invalidInput);
    return inputInt;
}

void printFarewell(int correct, int incorrect) {
    int totalGuesses = correct + incorrect;
    float percentCorrect;
    if (totalGuesses > 0)
        percentCorrect = ((float) correct / (float) totalGuesses) *
        ONE_HUNDRED_PERCENT;
    else
        percentCorrect = 0.0;
    
    cout << "Thanks for playing. Your final score was: \n";
    cout << "Correct Guesses: " << correct << std::endl;
    cout << "Incorrect Guesses: " << incorrect << std::endl;
    cout << "Total Guesses: " << totalGuesses << std::endl;
    cout << "Guess Percentage: " << percentCorrect << "%\n";
    if (percentCorrect > FIFTY_PERCENT)
        cout << "Nice Work!";
    else
        cout << "Better luck next time!";
    cout << std::endl << "Goodbye!" << std::endl;
}

void printWelcome(void) {
    cout << "Welcome to the Sequence Enumeration Guessing Game!\n";
    cout << "Would you like to review the rules before the game starts? [y/n] ";
    char userInput = std::cin.get();
    if (userInput == 'y' || userInput == 'Y') {
        cout << std::endl << std::endl;
        cout << "Rules: The game begins by the player selecting the length of\n"
        "a word. A word of that length is then used to generate\na SequenceEnum"
        " variation of itself, which is then displayed\nto the player. The "
        "player has 3 guesses to guess what the original\nword was before"
        " it was modified by the SequenceEnum. After 3 incorrect\nguesses, "
        "the game will let the player know what the word they have been\ntrying"
        " to guess actually is." << std::endl;
    }
    clearInputStream();
    cout << std::endl;
}

//I need to clear the input stream frequently enough to justify doing it as its
//own function
void clearInputStream(void) {
    std::cin.clear();
    std::fflush(stdin);
}

void doUserGuess(SequenceEnum* word, int& correct, int& incorrect) {
    int userGuessCounter = 0;
    bool userWordGuessCorrect = false;
    do {
        clearInputStream(); //clear any leftover input in input stream
        
        cout << "Can you guess what this word was before it was\nmodified by "
        "the SequenceEnum?\n";
        cout << "Modified word to guess: " << word->emitWord() << std::endl;
        cout << "Enter your guess: ";
        //std::cin >> std::ws;  // eat up any leading white spaces
        string userWordGuess;
        std::cin >> userWordGuess;
        if (word->guessWord(userWordGuess)) {
            correct++;
            cout << "\nCORRECT! Way to go!\n";
            userWordGuessCorrect = true;
        }
        else {
            incorrect++;
            userGuessCounter++;
            cout << "\nWrong! Try again. You entered: " << userWordGuess;
            if (userGuessCounter >= MAX_GUESSES) {
                cout << "\nUh-oh! You used up all your guesses...\n";
                cout << "The word you were trying to guess was: ";
                if (word->getSeqEnumIsActive()) {
                    word->toggleSeqEnumActivation();
                }
                else { //Turn off other seqEnum type, then turn off this one so
                    //everything is off
                    word->toggleSeqEnumActivation();
                    word->toggleSeqEnumActivation();
                }
                cout << word->emitWord();
                word->toggleSeqEnumActivation(); //Turn back on seqEnum
                cout << std::endl;
                return;
            }
            else {
                cout << std::endl << "Please try again. Guesses remaining: ";
                cout << MAX_GUESSES - userGuessCounter;
                cout << std::endl;
            }
        }
    } while (!userWordGuessCorrect);
}


//This function loops through each array of words of a certain length, counts
//the number of words in each array, and then puts those counts in a seperate
//array to keep track of their lengths
void countWordsOfEachLength(int * lengthsArray) {
    int counter = 0;
    lengthsArray[ZERO_LETTERS] = 0; //There are no 0 letter words
    lengthsArray[ONE_LETTER] = 0; //There are no 1 letter words
    lengthsArray[TWO_LETTERS] = 0; //There are no 2 letter words
    //Count number of 3 letter words
    for (string s : wrd3Ltr)  //Range-based for loops rule!
        counter++;
    
    lengthsArray[THREE_LETTERS] = counter;
    counter = 0; //reset counter
    //count the number of 4 letter words
    for (string s : wrd4Ltr)  //Range-based for loops rule!
        counter++;

    lengthsArray[FOUR_LETTERS] = counter;
    counter = 0; //reset counter
    //Count number of 5 letter words
    for (string s : wrd5Ltr)  //Range-based for loops rule!
        counter++;
    lengthsArray[FIVE_LETTERS] = counter;
    counter = 0; //reset counter
    //count the number of 6 letter words
    for (string s : wrd6Ltr)  //Range-based for loops rule!
        counter++;
    lengthsArray[SIX_LETTERS] = counter;
    counter = 0; //reset counter
    //Count number of 7 letter words
    for (string s : wrd7Ltr)
        counter++;
    lengthsArray[SEVEN_LETTERS] = counter;
    counter = 0; //reset counter
    //count the number of 8 letter words
    for (string s : wrd8Ltr)
        counter++;
    lengthsArray[EIGHT_LETTERS] = counter;
    counter = 0; //reset counter
    //Count number of 9 letter words
    for (string s : wrd9Ltr)
        counter++;
    lengthsArray[NINE_LETTERS] = counter;
    counter = 0; //reset counter
    //count the number of 10 letter words
    for (string s : wrd10Ltr)
        counter++;
    lengthsArray[TEN_LETTERS] = counter;
    counter = 0; //reset counter
    //Count number of 11 letter words
    for (string s : wrd11Ltr)
        counter++;
    lengthsArray[ELEVEN_LETTERS] = counter;
    counter = 0; //reset counter
    //count the number of 12 letter words
    for (string s : wrd12Ltr)
        counter++;
    lengthsArray[TWELVE_LETTERS] = counter;
}
