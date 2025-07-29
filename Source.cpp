#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <chrono>
#include <thread>

using namespace std;

//--- Data Structures ---//

// Struct to hold all Datee (the person you are dating) information
struct Datee {
    string name;
    string hairLength;
    string hairColor;
    string eyeColor;
    string lipColor;
    string skinTone;
};

// A dialogue node with 3 options and next-node indices
struct DialogueNode {
    string text;
    array<string, 3> options;
    array<int, 3> next;
};

//--- Helper Functions ---//

// Print text with a typing effect
void typeText(const string& text, unsigned int ms_per_char = 30) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(ms_per_char));
    }
}

// Creates a DialogueNode from given parameters
DialogueNode createNode(const string& text,
    const array<string, 3>& opts,
    const array<int, 3>& nxt) {
    return DialogueNode{ text, opts, nxt };
}

// Runs a node: prints text with speed, options, reads choice, returns next node index
int runNode(const vector<DialogueNode>& nodes, int nodeId) {
    const DialogueNode& node = nodes[nodeId - 1];  // nodes are 1-based

    // display dialogue text with typing effect
    typeText("\n" + node.text + "\n");

    // display options quickly
    for (int i = 0; i < 3; ++i) {
        cout << "(" << (i + 1) << ") " << node.options[i] << "\n";
    }
    cout << "> ";

    int choice = 0;
    while (true) {
        cin >> choice;
        if (choice >= 1 && choice <= 3) break;
        cout << "Please enter 1, 2, or 3: ";
    }

    return node.next[choice - 1];
}

//--- Main Program ---//
int main() {
    // 1) Gather Datee information
    Datee datee;
    cout << "What is your name? ";
    string playerName;
    getline(cin, playerName);

    cout << "Who are you dating? (name) ";
    getline(cin, datee.name);
    cout << "Hair length? (e.g. long, short) ";
    getline(cin, datee.hairLength);
    cout << "Hair color? ";
    getline(cin, datee.hairColor);
    cout << "Eye color? ";
    getline(cin, datee.eyeColor);
    cout << "Lip color? ";
    getline(cin, datee.lipColor);
    cout << "Skin tone? ";
    getline(cin, datee.skinTone);

    // 2) Build dialogue nodes
    vector<DialogueNode> nodes;

    //Node 1
    nodes.push_back(createNode(
        "You are on a date with " + datee.name + ". She walks into the restaurant.\nShe is wearing a slim black dress, " + datee.hairLength + " " + datee.hairColor + " hair, " + datee.eyeColor + " eyes, and " + datee.lipColor + " lips. She has a " + datee.skinTone + " complexion. She looks amazing as she reaches your table",
        { "*Run away*", "Hey " + datee.name + ", you look very nice.", "*Check weather app*" },
        { 0, 2, 3 }
    ));

    //Node 2 (path 1)
    nodes.push_back(createNode(
        "Thank you " + playerName + ", You look handsome.",
        { "Only my mom can call me that.", "Thank you. So tell me about yourself.", "Want to see something rad?" },
        { 0, 4, 5 }
    ));

    //Node 3 (path 2)
    nodes.push_back(createNode(
        "Ummm... is it supposed to storm?",
        { "No, I just love this app.", "Yeah big tornado outside.", "Just seeing if you show up on the radar." },
        { 6, 7, 0 }
    ));

    //Node 4 (path 1.1)
    nodes.push_back(createNode(
        "Well I am studying interior design, and i work part-time at a night club.",
        { "OMG I love interior design.", "That's so lame honestly. I like women who know how to cook though.", "What do you do for the club?" },
        { 8, 0, 9 }
    ));

    //Node 5 (path 1.2)
    nodes.push_back(createNode(
        "Oh... yes please...",
        { "*Do a backfilp*", "*Slam a chair on the ground WWE style*", "*Give her your best chad face*" },
        { 10, 11, 0 }
    ));

    //Node 6 (path 2.1)
    nodes.push_back(createNode(
        "I like a simple man...",
        { "*Make animal noises*", "I just want to make sure you don't get in bad weather later.", "Im not simple!" },
        { 12, 13, 0 }
    ));

    //Node 7 (path 2.2)
    nodes.push_back(createNode(
        "OH NO!!! HOW IS THERE A TORNADO IN ALASKA?! WE NEED TO RUN!!!",
        { "I was just kidding.", "*Take her hand and run outside*", "*Take her hand and run to the basement (yeah the kitchen has a basement)*" },
        { 0, 14, 15 }
    ));

    //Node 8 (path 1.1.1)
    nodes.push_back(createNode(
        "Oh really? Brace yourself, because we could talk about that until the sun burns out.First, there is color theory—most people pick a shade at random, but you need to think about hue, saturation, and value, and how they work together.A saturated blue will feel cool and recede, but a muted blue can feel warm if it has red undertones; without the right balance you end up with a room that feels like a cave or an ice rink.Then you layer on finishes : matte, eggshell, satin, semi - gloss, or high - gloss.Each one reflects light differently and shows imperfections in drywall or plaster work.Don’t even start on the ’ultra - matte’ finishes—they absorb so much light they look like black holes, but they show every fingerprint. Next is flooring.Hardwood species alone is a battle : white oak versus red oak versus walnut, each with its own Janka hardness rating.Engineered planks give stability, but the veneer thickness changes how many times you can sand it.Vinyl planks look like wood but feel plastic, and porcelain tile might be perfect for moisture but is as cold as ice under bare feet.You have to pick the right grout color, too, because gray grout in white tile screams 1980s hotel lobby. Millwork is another obsession.Crown molding needs to be sized to ceiling height—rule of thumb is half an inch per foot.A 9 - foot ceiling wants 4.5 - inch crown, but you may choose a 6 - inch for drama or a 3 - inch for minimalism.Baseboards must match the style : craftsman, colonial, or contemporary flat.Door casings, window trim, chair rails, wainscoting—even newels and balusters on staircases demand an eye for proportion and symmetry. Lighting design is critical : ambient, task, and accent layers.Recessed cans give overall light; under - cabinet tape lights help you chop vegetables safely; picture lights highlight your favorite art.All must be on dimmers, ideally with smooth fade curves.You must coordinate color temperature—never mix 2700K with 4000K, or people look jaundiced in one corner and clinical in another. Textiles are worse.Rugs must be sized so at least the front legs of your sofa sit on the pile.Window treatments require track systems hidden in soffits, with sheers for daytime and blackout liners for sleeping.Throw pillows demand a mix of patterns and solids, and upholstery fabric must be chosen for durability, stain resistance, and fade resistance if you have pets or kids.Even the trim on a lumbar pillow can ruin the effect if it’s a shade off. And don’t forget ergonomics.Chair seat heights, sofa depths, countertop overhangs—all must meet human scale.There is a reason kitchen islands are 36 inches high, not 34 or 38. Bathroom vanities need knee clearance that meets building codes, and stair risers and treads must follow strict ratios or you trip and sue someone. So when you say ‘interior design, ’ remember it is an intricate symphony of art, science, psychology, and building codes.It is not just picking pretty colors—it is sweat, measurements, testing, and endless revisions until every surface, every light, every texture is in perfect harmony.And that, my friend, is why we charge by the square foot.",
        { "SHUT UPPPPP!", "...", "HAHAHAHAHA" },
        { 0, 16, 17 }
    ));

    //Node 9 (path 1.1.2)
    nodes.push_back(createNode(
        "I am a DJ. I just play music and act cool and stuff.",
        { "What kind of music you into?", "Sounds fun, maybe ill come see you do your thing.", "Oh yeah i love music, especially NBA Young Boy" },
        { 18, 19, 0 }
    ));
    //Node 10 (path 1.2.1)
    nodes.push_back(createNode(
        "*You get on the ground and do a backwards roll.* Wow that was so... rad...",
        { "*Do another one*", "Im sorry, my flip skill wasn't high enough.", "Hide under the table*" },
        { 21, 22, 0 }

    ));
    //Node 11 (path 1.2.2)
    nodes.push_back(createNode(
        "*You slam the prop chair on the ground and it breaks into a million pieces*\nWOW... can I have your autograph?",
        { "No, can't after my fight with Alligator Man", "YES PWEASE", "Sure, after you buy me dinner." },
        { 22, 0, 23 }
    ));

    //Node 12 (path 2.1.1)
    nodes.push_back(createNode(
        "*She blushes* what a little cutie, I could just take you home.",
        { "*Make seductive animal noises", "Mommy, take me home *Lay on the floor reaching to " + datee.name + ".", "*Switch to Australian accent* Oy mate, that was just me animal calls for when me gow ouut to fight the damn'd Ostriches in ou neva ending war for peace." },
        { 24, 25, 0 }
    ));

    //Node 13 (path 2.1.2)
    nodes.push_back(createNode(
        "Oh, well that's very kind of you. Sorry for calling you simple.",
        { "Don't sweat it. What are you going to order?", "Ill forgive you if I get a kiss later.", "Im too complex for you, I guess my dog was right about this date." },
        { 26, 27, 0 }
    ));

    //Node 14 (path 2.2.1)
    nodes.push_back(createNode(
        "*You grab her hand and run outside. The wind is howling. In the dark, a silhouette of something menacing is lit up by lightning*\n What do we do?!",
        { "*Go to your car*", "*Let go of her hand and run to a conveniently placed one-person bunker", "If we die, at least we'll die together. *Let storm take you both*" },
        { 28, 0, 29 }
    ));
    //Node 15 (path 2.2.2)
    nodes.push_back(createNode(
        "*You run to the kitchen basement. It is lit by one dim bulb hanging from the ceiling. Air whistles through cracks in the ceiling*\n*" + datee.name + " shakes uncontrollably.* Are we going to die?",
        { "*Comfort her* We are in the right spot for something like this.", "Yeahhh thats what my weather app says.", "Yes *Let storm take you both*" },
        { 30, 0, 29 }
    ));
    //Node 16 (path 1.1.1.1)
    nodes.push_back(createNode(
        "Oh... I'm sorry. I got carried away. What do you do?",
        { "I am studying.", "I work full-time.", "I love anime thighs." },
        { 31, 32, 0 }
    ));

    //Node 17 (path 1.1.1.2)
    nodes.push_back(createNode(
        "*Blushes* I didn't think it was that good, but thanks. You're a good listener.",
        { "*Descend into madness*", "I think you're interesting.", "You talk too much girl." },
        { 33, 34, 0 }
    ));

    //Node 18 (path 1.1.2.1)
    nodes.push_back(createNode(
        "Oh I love Indie Folk and J-Pop. I don't play that at the club though. I have to play whatever gets the crowd hyped.",
        { "What gets the crowd hyped?", "Absolute garbage music taste.", "I like chill music too." },
        { 35, 0, 36 }
    ));

    //Node 19 (path 1.1.2.2)
    nodes.push_back(createNode(
        "Only if you want me to see me pretending to be super cool and awesome.\nBut don't. if you really want to hear my music we can cruise sometime.",
        { "You seem pretty cool and awesome.", "I'd like that.", "No I want to meet your coworkers and give you song requests." },
        { 37, 37, 0 }
    ));

    //Node 20 (path 1.2.2.1)
    nodes.push_back(createNode(
        "*You tell her about you fight with Alligator Man and how he destroyed your kids with the power of microplastics* \nOh you're so heroic and stuff, but I don't think I can go without having children. Sorry",
        { "Okay I understand.", "DAMN YOU ALLIGATOR MAN!!!", "I don't even like kids." },
        { 0, 0, 0 }
    ));

    //Node 21 (path 1.2.1.1)
    nodes.push_back(createNode(
        "*She gets hypnotized by your flips and falls in love with you. You get married. YAY!",
        { "Flip", "Flip", "Flip" },
        { 0, 0, 0 }
    ));

    //Node 22 (path 1.2.1.2)
    nodes.push_back(createNode(
        "Well come back when you get better nerd.",
        { "Fine", "Gosh dang it!", "WAAAA" },
        { 0, 0, 0 }
    ));

    //Node 23 (path 1.2.2.2)
    nodes.push_back(createNode(
        "Okay I think I can be patient...",
        { "What's your count?", "...", "So... what are you going to eat?" },
        { 0, 38, 26 }
    ));

    //Node 24 (path 2.1.1.1)
    nodes.push_back(createNode(
        "She barks back at you, and you both devolve into inaudible creatures.",
        { "APES TOGETHER STRONG", "*EEEOOOOEOOOO*", "ooooo ooooo aaaaa aaaaa" },
        { 39, 0, 0 }
    ));

    //Node 25 (path 2.1.1.2)
    nodes.push_back(createNode(
        "*" + datee.name + " picks you up like a toddler and carries you home.\nShe puts you in a crib (idk where she got it, or how you fit in there) and tucks you in.",
        { "*In a Patrick Warburton voice* Thanks for treating me so kindly ma'am. I really am just a simple man.", "*break out of the crib and steal her stuff*", "I want a huggg" },
        { 40, 41, 42 }
    ));

    //Node 26 (path 2.1.2.1)
    nodes.push_back(createNode(
        "Idk something healthy I guess. I've been trying to eat better.",
        { "Damn yeah get a salad or something", "Me too, its so hard though.", "I'm going to get the Cheese." },
        { 0, 43, 44 }
    ));

    //Node 27 (path 2.1.2.2)
    nodes.push_back(createNode(
        "*smiles* We'll see. I don't think that deserves a kiss, but treat me well, and you might get one.",
        { "I wrote you a poem just for this situation.", "But i'm a really good kisser. Self-proclaimed even.", "Girl I can't wait to feel those wet plumpy lips on mine." },
        { 45, 46, 0 }
    ));

    //Node 28 (path 2.2.1.1)
    nodes.push_back(createNode(
        "*You both run to your car and drive away from the tornado.\nYou spot an old chemistry building with a bomb shelter sign on it. Go in?*",
        { "*Yes*", "*No*", "Hey so have you seen Game Of Thrones? Its an HBO series about a bunch of kingdoms vying for power after some stuff happens to Ned. I won't say too much, but he gets decapitated by king Geoffery. Its a great show." },
        { 47, 48, 0 }
    ));

    //Node 29 (path 2.2.1.2)
    nodes.push_back(createNode(
        "You vanish under the storm, and you wake up alone with a rusty sword.\nYou look up and see a castle under the eye of a raging storm.\n You don't know where " + datee.name + " is, but you assume she is being held captive there, because you played Mario.",
        { "ehhh I guess I'll just die.", "*start walking towards the castle*", "Look for grimoires in a bush." },
        { 0, 49, 50 }
    ));

    //Node 30 (path 2.2.2.1)
    nodes.push_back(createNode(
        "*She embraces you, and after a long time, the wind calms and the sun rises. You step outside with " + datee.name + " by your side* Want to keep this date going, heroic guy?",
        { "nah see ya later dud", "Yeah, lets go to the park.", "Yeah, lets go to my place." },
        { 0, 51, 52 }
    ));

    //Node 31 (path 1.1.1.1.1)
    nodes.push_back(createNode(
        "Oh yeah? What do you study?",
        { "Masters in Dinosuarous Rex Philosphy", "PHD in Being Super Sexy and Stuff", "Anime Girl Thighs" },
        { 53, 53, 0 }
    ));

    //Node 32 (path 1.1.1.1.2)
    nodes.push_back(createNode(
        "Oh yeah? Where do you work?",
        { "Freddy Fazbear's Pizza", "I trade crypto.", "I am The President of The United States of America." },
        { 54, 0, 55 }
    ));

    //Node 33 (path 1.1.1.2.1)
    nodes.push_back(createNode(
        "*You can't stop laughing... and you start dancing on the table.\nPeople try to stop you, but they end up dancing and laughing with you*",
        { "*stop*", "*There is no stopping*", "~`!@#$%^&*()_+={}[]|;:<>,.?/~~!!?!?~~~***---!!!" },
        { 56, 56, 56 }
    ));

    //Node 34 (path 1.1.1.2.2)
    nodes.push_back(createNode(
        "*She gives you a kiss on your hand* Thank you.",
        { "That was my first kiss", "Oh yeah... mark that shit up...", "What other passions do you have?" },
        { 57, 0, 58 }
    ));

    //Node 35 (path 1.1.2.1.1)
    nodes.push_back(createNode(
        "Oh yk Drake, Future, all those people. I don't really mess with the misogynistic lines, but it does make the club fun.",
        { "I don't listen that deeply, I just like it cause its fun too.", "Im not too into that music.", "Really? I like how they talk about women." },
        { 36, 36, 0 }
    ));

    //Node 36 (path 1.1.2.1.2)
    nodes.push_back(createNode(
        "Really? So what artists do you like?",
        { "(Your favorite Bands/artists)", "NBA YB!!!!!", "DJ KHALIDDDDDD!!! WE THE BEST MUSICCCCC!!! ALL I DO IS WIN WIN WIN NMW!!!" },
        { 59, 0, 0 }
    ));

    //Node 37 (path 1.1.2.2.1)
    nodes.push_back(createNode(
        "*" + datee.name + " blushes* Sooo... do you workout? You look like you workout.",
        { "Yeah I try to stay consistant about it. Do you?", "Nah, but Im glad you like what you see! Do you?", "My primary motivation is seeing that gym booty every morning." },
        { 60, 60, 0 }
    ));

    //Node 38 (path 1.2.2.2.1)
    nodes.push_back(createNode(
        "I'm ready to go, shall we?",
        { "*Go to the bathroom*", "*Go to her house*", "Hey language!!" },
        { 61, 62, 0 }
    ));

    //Node 39 (path 2.1.1.1.1)
    nodes.push_back(createNode(
        "You both reenact the whole Planet of The Apes Trilogy. People watch and rate it high on IMDB.",
        { "APES TOGETHER STRONG", "7/10", "10/10" },
        { 0, 0, 0 }
    ));

    //Node 40 (path 2.1.1.2.1)
    nodes.push_back(createNode(
        "You fall asleep in the crib and you live a wonderful life... every simple man envies you.",
        { "And for your information, I prefer sugar free artificial sweeteners made by man!", "You know what? I don’t even like honey. I don’t eat it!", "WHY IS YOGURT NIGHT SO DIFFICULT?!" },
        { 0, 0, 0 }
    ));

    //Node 41 (path 2.1.1.2.2)
    nodes.push_back(createNode(
        "You break out of the crib and put on the stripped black and white robber suit that you had in your back pocket.\nYou sneak around and spot the original Starry Night. You stuff it in your back pocket.\n" + datee.name + " sees you and calls the cops while she loads her revolver.",
        { "*Jump out the nearest open window*", "*run to her creepy dark basement*", "Haha get pranked nerd" },
        { 63, 64, 0 }
    ));

    //Node 42 (path 2.1.1.2.3)
    nodes.push_back(createNode(
        "*She comforts you with a warm hug and kind words.*",
        { "I can die happy", "...", "Gross" },
        { 0, 0, 0 }
    ));

    //Node 43 (path 2.1.2.1.1)
    nodes.push_back(createNode(
        "Yeah it is. I struggle with shit like that, but I think I am getting better.\nDo you struggle with anything?",
        { "This is too deep for me my guy", "Yeah (whatever you struggle with)", "Not too much." },
        { 0, 65, 66 }
    ));

    //Node 44 (path 2.1.2.1.2)
    nodes.push_back(createNode(
        "Oh, uhhh okay. *The waitress brings you a slice of cheese from a wheel*",
        { "*eat it in one fell swoop (will lead to death)*", "*eat it slowly while keeping eye contact*", "This cheese reminds me of you girl" },
        { 0, 67, 0 }
    ));

    //Node 45 (path 2.1.2.2.1)
    nodes.push_back(createNode(
        "Oooo okay tell me!",
        { "Don't be a fool now\nThe end is nigh and birds sing\nEveryone has to die", "Girl you look like fire\nDangerous, my hearts desire\nShine your light on me", "Aye this a diss track\nYou look stupid,thats a fact\nGive up the cool act" },
        { 68, 69, 0 }
    ));

    //Node 46 (path 2.1.2.2.2)
    nodes.push_back(createNode(
        "Yeah? prove it",
        { "*Make out with the puppet hand you just formed*", "*Kiss her hand*", "*Show her the video of you making out with a pillow*" },
        { 70, 71, 0 }
    ));

    //Node 47 (path 2.2.1.1.1)
    nodes.push_back(createNode(
        "*You ram your car into the building and get out.\n You see the shelter ahead. Its an old cold war bunker.\n You both open the large door and step inside, closing it behind you.*\nIts so nice to be [redacted]. I wish I could be [redacted].",
        { "Huh?", "What did you say?", "What do you mean [redacted]?" },
        { 72, 72, 72 }
    ));

    //Node 48 (path 2.2.1.1.2)
    nodes.push_back(createNode(
        "*You get a feeling of relieve passing by the building*\n *The tornado dies off and the beauty of post-storm takes the scene*\n Its so beautiful.",
        { "I literally can't see anything.", "Im happy to be here with you.", "*take her hand*" },
        { 0, 73, 74 }
    ));

    //Node 49 (path 2.2.1.2.1)
    nodes.push_back(createNode(
        "*You head towards the castle. You descend into a poison swamp and your poison meter fills up*\n *Somewhere, you hear a voice say:\nSomething beautiful needs something depraved or tragic to embolden that beauty. Also I love poison swamps RAHAHAHAHA",
        { "I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquellq. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella. I am Malenia, blade of Miquella.", "I don't even like FromSoft games", "*speedrun through it*" },
        { 75, 0, 76 }
    ));

    //Node 50 (path 2.2.1.2.2)
    nodes.push_back(createNode(
        "*You fall into the bush and get stuck. You find a Grimoire called \"Zoltraak\"*\n*You see " + datee.name + " fighting a demon in the distance*",
        { "*Go help her*", "*Find more grimoires*", "*Give up*" },
        { 77, 78, 0 }
    ));

    //Node 51 (path 2.2.2.1.1)
    nodes.push_back(createNode(
        "*You both head to a nearby park* Hey... wanna make out?",
        { "Yes", "Yes", "Yes (but with a voice crack)" },
        { 79, 79, 79 }
    ));

    //Node 52 (path 2.2.2.1.2)
    nodes.push_back(createNode(
        "*You both head to your house* Hey... want to make out?",
        { "Yes", "Yes", "Yes" },
        { 79, 79, 79 }
    ));

    //Node 53 (path 1.1.1.1.1.1)
    nodes.push_back(createNode(
        "Oh damn that's sick asf. At least you didn't say anime thighs or something like that.",
        { "Oooo now that you mention it...", "Nah I just like normal people thighs (lie)", "But 2B tho..." },
        { 80, 80, 80 }
    ));

    //Node 54 (path 1.1.1.1.2.1)
    nodes.push_back(createNode(
        "Wait you work here? That's so cool! I love the animatronics in here!\n *Suddenly... everyone leaves and your shift starts. You both head towards your office.*",
        { "Oh no...", "YESSS", "Chicka kinda bad  tho..." },
        { 81, 81, 0 }
    ));

    //Node 55 (path 1.1.1.1.2.2)
    nodes.push_back(createNode(
        "*secret service busts in through the windows, walls, ceiling, floors, and fake grandmas and arrests " + datee.name + "*",
        { "I always knew you were an alien!", "I always knew you were a grandma!", "I always knew you were YB fan!" },
        { 82, 82, 82 }
    ));

    //Node 56 (path 1.1.1.2.1.1)
    nodes.push_back(createNode(
        "The world goes mad with Dance Fever, and the last song ever sung screams out months after.",
        { "...", "...", "..." },
        { 0, 0, 0 }
    ));

    //Node 57 (path 1.1.1.2.2.1)
    nodes.push_back(createNode(
        "*She thinks your joking*",
        { "No really that was my fist kiss", "*Start making out with your hand*", "So what are you passionate about?" },
        { 0, 70, 58 }
    ));

    //Node 58 (path 1.1.1.2.2.2)
    nodes.push_back(createNode(
        "Im really into video games, music, art, and movies. I also like to cook! Hey, so im getting pretty tired. Wanna walk me home?",
        { "Yeah sure", "Nah go ahead", "Its omly 3am!" },
        { 83, 0, 0 }
    ));

    //Node 59 (path 1.1.2.1.2.1)
    nodes.push_back(createNode(
        "You'll have to play them for me sometime...",
        { "I got you after our dinner", "No I am gatekeeping", "LETS LISTEN TO IT RIGHT NOW!!!" },
        { 84, 0, 85 }
    ));

    //Node 60 (path 1.1.2.1.2.2)
    nodes.push_back(createNode(
        "Yeah I workout a lot actually. It clears my head yk?",
        { "Nah it fills me with RAGE *Break Prop chair by you*", "Yeah totally, its nice to do something good for my body.", "Im glad it brings you clarity. I feel so much better afterwards too." },
        { 11, 86, 86 }
    ));

    //Node 61 (path 1.2.2.2.1.1)
    nodes.push_back(createNode(
        "*You go to the bathroom with her, and you fall deeper in your pit.\n You can climb out, but you need to take action.",
        { "...", "...", "..." },
        { 0, 0, 0 }
    ));

    //Node 62 (path 1.2.2.2.1.2)
    nodes.push_back(createNode(
        "*You step inside her home. It is cozy and clean\n She thought it would fulfill her loneliness, but she numbs it instead of facing it.\nToo much sex muddies the mind.",
        { "...", "...", "..." },
        { 0, 0, 0 }
    ));

    //Node 63 (path 2.1.1.2.2.1)
    nodes.push_back(createNode(
        "You jump out her 100th story window. Too bad you weren't bitten by a radioactive spider.",
        { "...", "...", "..." },
        { 0, 0, 0 }
    ));

    //Node 64 (path 2.1.1.2.2.2)
    nodes.push_back(createNode(
        "*You remember " + datee.name + " is an old blind vet as you try to hide.\nShe is searching for you, trying to hear the slightest movement in the dark basement*\nYou see a cellar door, a gun, and a bag of chips",
        { "door", "gun", "chips" },
        { 87, 88, 0 }
    ));

    //Node 65 (path 2.1.2.1.1.1)
    nodes.push_back(createNode(
        "Damn, well im happy you haven't given up. It can be tempting to give in.",
        { "Yeah it can.", "Thank you.", "I wish I was in a fantasy land rn." },
        { 89, 89, 29 }
    ));

    //Node 66 (path 2.1.2.1.1.2)
    nodes.push_back(createNode(
        "Oh well... that's good.",
        { "Actually... I do struggle with (whatever you struggle with)", "...", "You jealous?" },
        { 65, 0, 0 }
    ));

    //Node 67 (path 2.1.2.1.2.1)
    nodes.push_back(createNode(
        "*You savor every bite, and " + datee.name + " leaves with a new phobia*",
        { "...", "...", "..." },
        { 0, 0, 0 }
    ));

    //Node 68 (path 2.1.2.2.1.1)
    nodes.push_back(createNode(
        "*As you sing your poem, your face spirals and the city starts to spin*",
        { "^&%&^%*&^", "#^@@((#^*&#", "!&#^&!@&#(" },
        { 0, 0, 0 }
    ));

    //Node 69 (path 2.1.2.2.1.2)
    nodes.push_back(createNode(
        "Okay okay... that deserves a kiss. *She sits closer to you and pecks your lips*\n Hey... I've really enjoyed this, but im getting tired. Wanna walk me home?",
        { "Yeah of course", "your breath stank", "Yes... and great kiss btw" },
        { 83, 0, 83 }
    ));

    //Node 70 (path 1.1.1.2.2.1.1)
    nodes.push_back(createNode(
        "*You maneuver you lips between your thumb and pointer finger and make a scene in front of everyone.\nShe was not impressed, because your mouth was gaping open over your hand the whole time*",
        { "That's how you're supposed to kiss??", "Should've let the hand take lead.", "Worth it." },
        { 0, 0, 0 }
    ));

    //Node 71 (path 1.1.1.2.2.1.2)
    nodes.push_back(createNode(
        "*You kiss her hand softly* Well idk how that proves anything... but Know I know you are a good kisser...somehow,\nCould you walk me home?",
        { "Yeah of course", "Most def", "Nar" },
        { 83, 83, 0 }
    ));

    //Node 72 (path 2.2.1.1.1.1)
    nodes.push_back(createNode(
        "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! " + "I want to be " + playerName + "!!! ",
        { "[REDACTED]", "[REDACTED]", "[REDACTED]" },
        { 0, 0, 0 }
    ));

    //Node 73 (path 2.2.1.1.2.1)
    nodes.push_back(createNode(
        "I am happy to be here with you too *kisses your cheek as you ride off into the sunset*",
        { "...", "...", "..." },
        { 100, 100, 100 }
    ));

    //Node 74 (path 2.2.1.1.2.2)
    nodes.push_back(createNode(
        "*You take her hand as you ride into the sunset*",
        { "...", "...", "..." },
        { 100, 100, 100 }
    ));
    //Node 75 (path 2.2.1.2.1.1)
    nodes.push_back(createNode(
        "*suddenly, a lady with a badass sword and armor comes swinging relentlessly at you, and you die instantly.\nShe doesn't even say it because you have so much already.",
        { "...", "...", "..." },
        { 0, 0, 0 }
    ));

    //Node 76 (path 2.2.1.2.1.2)
    nodes.push_back(createNode(
        "You speedrun the whole thing and get married and die with " + datee.name + ". ",
        { "Wish I took my time.", "LETS GOOOO", "PR" },
        { 0, 0, 0 }
    ));

    //Node 77 (path 2.2.1.2.2.1)
    nodes.push_back(createNode(
        "*You help her slay the demon with your new magic powers* Hey i'm tired, can you take me home?",
        { "Yeah of course", "No i want to stay", "I think you mean \"Thank You.\"" },
        { 83, 0, 0 }
    ));

    //Node 78 (path 2.2.1.2.2.2)
    nodes.push_back(createNode(
        "You never stop looking for more grimoires...never.",
        { "...", "...", "..." },
        { 0, 0, 0 }
    ));

    //Node 79 (path 2.2.2.1.1.1)
    nodes.push_back(createNode(
        "*She gets on top of you and kisses you.",
        { "*Go further*", "*enjoy the moment*", "You kinda heavy ngl" },
        { 91, 92, 0 }
    ));

    //Node 80 (path 1.1.1.1.1.1.1)
    nodes.push_back(createNode(
        "You cannot deny your love of anime thighs and leave to go look at them. Sorry, but im trying to be realisitic here yk?",
        { "Yeah you right", "But im not even into anime thighs?!?!(lie)", "I would never do this(lie)" },
        { 0, 0, 0 }
    ));

    //Node 81 (path 1.1.1.1.2.1.1)
    nodes.push_back(createNode(
        "*Freddy comes in and sees you both in masks*\nHe walks up to you and slides your mask off*\n You think you can fool me with your little masks?! you insult me.\n*He stuff both of you into a suit, and calls it Dumb Idiot*",
        { "THE LORE", "I don't get this reference", "The bite of 87' is fake" },
        { 0, 0, 0 }
    ));

    //Node 82 (path 1.1.1.1.2.2.1)
    nodes.push_back(createNode(
        "How did you know?!",
        { "Im just so cool (explosions)", "Im just so awesome (bigger explosions)", "MERICAAAA (Biggest explosion)" },
        { 0, 0, 0 }
    ));

    //Node 83 (path 1.1.1.2.2.2.1)
    nodes.push_back(createNode(
        "*You walk her home as the crickets and street lights begin their ritual.\n You can stay the night if you want... but no funny business. I want to take my time with you.",
        { "Nooo", "Okay you got it, ill sleep wherever you want me to.", "I can't, but thank you. Maybe I can another time!" },
        { 62, 90, 93 }
    ));

    //Node 84 (path 1.1.2.1.2.1.1)
    nodes.push_back(createNode(
        "*You both decide to cruise as the sun is going down. What song do you play?*",
        { "Outside Today by YB", "Sittin' On The Dock of The Bay by Otis Redding", "Par 5 by Kitty Craft" },
        { 0, 94, 94 }
    ));

    //Node 85 (path 1.1.2.1.2.1.2)
    nodes.push_back(createNode(
        "*You take the boombox out of your pocket and jam Outside Today by YB, and everyone rushes you like a pitcher.",
        { "NOOO", "AHHHHH", "TRYNA HIDE FROM THA CAMERAS" },
        { 0, 0, 0 }
    ));

    //Node 86 (path 1.1.2.1.2.2.1)
    nodes.push_back(createNode(
        "Id like to workout with you sometime... but lets go, you need to walk me home man.",
        { "As long as you hype me up.", "As long as you talk down to me.", "As long as you tell me im a good boy." },
        { 83, 83, 83 }
    ));

    //Node 87 (path 2.1.1.2.2.2.1)
    nodes.push_back(createNode(
        "*You run for the door, but she's too good with the gun and stops you before you get close.\nMaybe watch the movie next time*",
        { "Okay yeah I will", "Nope", "Its on my watchlist" },
        { 0, 0, 0 }
    ));

    //Node 88 (path 2.1.1.2.2.2.2)
    nodes.push_back(createNode(
        "You grab the gun and take the safety off, but she hears it and shoots you before you can get a shot off.",
        { "dang it", "frick", "crap" },
        { 0, 0, 0 }
    ));

    //Node 89 (path 2.1.2.1.1.1.1)
    nodes.push_back(createNode(
        "Could you walk me home? This has been really nice.",
        { "Yeah for sure", "nar", "I already know where you live, you don't need to show me" },
        { 83, 0, 0 }
    ));

    //Node 90 (path 1.1.1.2.2.2.1.1)
    nodes.push_back(createNode(
        "Don't worry, Ill put you in the guest bedroom. There's a nice bed, and you will have your own bathroom.",
        { "That sounds nice.", "No I want to sleep with your dog, I need emotional support(She has one, but she doesn't remember telling you). ", "Actually lets sleep together!" },
        { 95, 96, 62 }
    ));

    //Node 91 (path 2.2.2.1.1.1.1)
    nodes.push_back(createNode(
        "*You do more intimate things with her. You go home after*",
        { "...", "...", "..." },
        { 0, 0, 0 }
    ));

    //Node 92 (path 2.2.2.1.1.1.2)
    nodes.push_back(createNode(
        "*You keep making out and stop when you need to catch your breath* This was nice... I want to see you again.",
        { "I want to see you again too.", "Nah you're a bad kisser.", "Tbh, I don't feel the same, I'm sorry." },
        { 97, 0, 0 }
    ));

    //Node 93 (path 1.1.1.2.2.2.1.2)
    nodes.push_back(createNode(
        "Okay that's cool *kisses you* Goodnight " + playerName + ".",
        { "Goodnight " + datee.name + ".", "I love you girl", "See ya!" },
        { 100, 0, 0 }
    ));

    //Node 94 (path 2.2.2.1.1.1.2)
    nodes.push_back(createNode(
        "Oooo nice, I love this song. *kisses your cheek as you play songs through the night.",
        { "...", "...", "..." },
        { 100, 100, 100 }
    ));

    //Node 95 (path 1.1.1.2.2.2.1.1.1.1)
    nodes.push_back(createNode(
        "*She opens the door to her cozy little home. Its filled with plants and books*\n This is my humble abode",
        { "Its very homey, I like your plants", "Its very clean, I like your book collection.", "This place is absolute garbage!" },
        { 98, 98, 0 }
    ));

    //Node 96 (path 1.1.1.2.2.2.1.1.1.2)
    nodes.push_back(createNode(
        "Oh... uh i get that i guess... *You run outside and sleep with the dog",
        { "YAYYYY", "LETS GOOOOO", "booooo" },
        { 100, 100, 0 }
    ));

    //Node 97 (path 1.1.1.2.2.2.1.2.2.2.1.1.1.2.1)
    nodes.push_back(createNode(
        "*You both part ways for the night, but the feeling of intimacy without shame stays with you all night.",
        { "...", "...", "..." },
        { 100, 100, 100 }
    ));

    //Node 98 (path 1.1.1.2.2.2.1.1.1.1.1)
    nodes.push_back(createNode(
        "Thank you!! You wanna watch a movie?",
        { "Nope i want dog", "*put on a scary movie*", "Nah I hate movies." },
        { 96, 99, 0 }
    ));

    //Node 99 (path 1.1.1.2.2.2.1.1.1.1.1.1)
    nodes.push_back(createNode(
        "*" + datee.name + " sits close to you*\n Wanna cuddle?",
        { "Yesss", "noooo", "with your dog!!!" },
        { 101, 0, 96 }
    ));

    //Node 100 (WIN)
    nodes.push_back(createNode(
        "You have successfully earned a second date. Good job!!!",
        { "...", "...", "..." },
        { 0, 0, 0 }
    ));

    //Node 101 (path 1.1.1.2.2.2.1.1.1.1.1.1.1)
    nodes.push_back(createNode(
        "*You cuddle with her and feel genuine connection.*",
        { "You wanna make out?", "*ditch 4 doggo", "*Be present with her*" },
        { 102, 96, 103 }
    ));

    //Node 102 (path 1.1.1.2.2.2.1.1.1.1.1.1.1.1)
    nodes.push_back(createNode(
        "yes... *She turns to face you and you both ignore the entire movie (it was corny anyways)*",
        { "You wanna go further?", "*Ditch 4 the main doggo!!*", "*Enjoy the moment*" },
        { 104, 96, 103 }
    ));

    //Node 103 (path 1.1.1.2.2.2.1.1.1.1.1.1.1.2)
    nodes.push_back(createNode(
        "*You feel so intimate with this woman, and she feels the same*\nYou can sleep with me in my room if you want... or we can fall asleep right here.",
        { "Lets stay here.", "I'll sleep with you in your room.", "It's cool, I wanna give you your space." },
        { 105, 106, 107 }
    ));

    //Node 104 (path 1.1.1.2.2.2.1.1.1.1.1.1.1.1.1.1)
    nodes.push_back(createNode(
        "It feels right, but let's keep this special.",
        { "*Be intimate with her*", "If you not fs, then we good right here.", "What's on your mind?" },
        { 0, 108, 109 }
    ));

    //Node 105 (path 1.1.1.2.2.2.1.1.1.1.1.1.1.2.1)
    nodes.push_back(createNode(
        "*You both fall asleep on the couch in each others arms*",
        { "...", "...", "..." },
        { 100, 100, 100 }
    ));

    //Node 106 (path 1.1.1.2.2.2.1.1.1.1.1.1.1.1.2.2)
    nodes.push_back(createNode(
        "Okay... follow me cutie",
        { "...", "...", "..." },
        { 110, 110, 110 }
    ));

    //Node 107 (path 1.1.1.2.2.2.1.1.1.1.1.1.1.1.2.3)
    nodes.push_back(createNode(
        "I really don't mind, but i appreciate you. You're sweet.",
        { "Okay, if you really don't mind.", "DOG", "Yeah, I'll let you get to bed... goodnight " + datee.name + "." },
        { 106, 96, 111 }
    ));

    //Node 108 (path 1.1.1.2.2.2.1.1.1.1.1.1.1.1.1.1.1)
    nodes.push_back(createNode(
        "Thanks... Im just not ready for that. *she kisses you deeply, and once the movie is over, she falls asleep with her head in your chest*",
        { "...", "...", "..." },
        { 100, 100, 100 }
    ));

    //Node 109 (path 1.1.1.2.2.2.1.1.1.1.1.1.1.1.1.1.2)
    nodes.push_back(createNode(
        "I want to... I just know that rushing can ruin some stuff, like we will never be at this stage in whatever we got going on again if we do it yk?",
        { "If we both want it, then I don't see the bad. I want you.", "Im with you on that, lets take it slow.", "As long as we commited to each other, I think it's okay yk?" },
        { 112, 108, 112 }
    ));

    //Node 110 (path 1.1.1.2.2.2.1.1.1.1.1.1.1.1.2.2.1)
    nodes.push_back(createNode(
        "*She leads you up to her room full of her art and her gaming setup.\n *She has her " + datee.hairLength + " hair in a bun, and some baggy pajamas.\nShe invites you to cuddle with her.\nShe tells you intimate things, and you do as well.\nThats connection, and it fulfills something that was empty before.",
        { "...", "...", "..." },
        { 100, 100, 100 }
    ));

    //Node 111 (path 1.1.1.2.2.2.1.1.1.1.1.1.1.1.2.3.1)
    nodes.push_back(createNode(
        "Goodnight " + playerName + ", sweet dreams! *She kisses you, and shows you to your room. She misses you all night, and you her, but both can't wait for morning.",
        { "...", "...", "..." },
        { 100, 100, 100 }
    ));

    //Node 112 (path 1.1.1.2.2.2.1.1.1.1.1.1.1.1.1.1.2)
    nodes.push_back(createNode(
        "You are intimate with her and don't want the night to end, and dread the morning to come.",
        { "...", "...", "..." },
        { 0, 0, 0 }
    ));

    // 3) Game loop
    int currentNode = 1;
    while (currentNode != 0) {
        currentNode = runNode(nodes, currentNode);
    }

    cout << "\nDate over. Thanks for playing " << playerName << "!\n";
    return 0;
}