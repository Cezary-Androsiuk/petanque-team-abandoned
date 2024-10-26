#include "DefaultPersonalizationData.h"

const char *defaultPlayerTypes =
R"(
{
    "junior":{
        "male": {
            "min": 0,
            "max": 18
        },
        "female": {
            "min": 0,
            "max": 18
        }
    },
    "youth": {
        "male": {
            "min": 18,
            "max": 23
        },
        "female": {
            "min": 18,
            "max": 23
        }
    },
    "senior": {
        "male": {
            "min": 23,
            "max": 55
        },
        "female": {
            "min": 23,
            "max": 50
        }
    },
    "veteran": {
        "male": {
            "min": 55,
            "max": 999
        },
        "female": {
            "min": 50,
            "max": 999
        }
    }
}
)";

const char *defaultExampleData =
R"(
{
    "teams": [
        {
            "team name": "Boule Masters",
            "players": [
                {
                    "fname": "Michael",
                    "lname": "Brown",
                    "license": "L1828",
                    "age": "43",
                    "gender": "M",
                    "isTeamLeader": true
                },
                {
                    "fname": "James",
                    "lname": "Williams",
                    "license": "L3119",
                    "age": "23",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "John",
                    "lname": "Anderson",
                    "license": "L4000",
                    "age": "47",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Emma",
                    "lname": "Wilson",
                    "license": "L3017",
                    "age": "23",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Daniel",
                    "lname": "Davis",
                    "license": "L2472",
                    "age": "28",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "John",
                    "lname": "Brown",
                    "license": "L8923",
                    "age": "46",
                    "gender": "M",
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Srebrne Kule",
            "players": [
                {
                    "fname": "Isabella",
                    "lname": "Williams",
                    "license": "L7277",
                    "age": "38",
                    "gender": "M",
                    "isTeamLeader": true
                },
                {
                    "fname": "Emma",
                    "lname": "Thomas",
                    "license": "L1581",
                    "age": "44",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Sophia",
                    "lname": "Johnson",
                    "license": "L1022",
                    "age": "30",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Thomas",
                    "license": "L3601",
                    "age": "20",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Williams",
                    "license": "L1060",
                    "age": "18",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Sophia",
                    "lname": "Thomas",
                    "license": "L2403",
                    "age": "47",
                    "gender": "M",
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Petanque Pasja",
            "players": [
                {
                    "fname": "Emma",
                    "lname": "Williams",
                    "license": "L3286",
                    "age": "29",
                    "gender": "F",
                    "isTeamLeader": true
                },
                {
                    "fname": "David",
                    "lname": "Davis",
                    "license": "L7003",
                    "age": "33",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Olivia",
                    "lname": "Johnson",
                    "license": "L7275",
                    "age": "41",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Miller",
                    "license": "L2834",
                    "age": "20",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "David",
                    "lname": "Brown",
                    "license": "L9907",
                    "age": "50",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Chris",
                    "lname": "Anderson",
                    "license": "L4332",
                    "age": "28",
                    "gender": "M",
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Stalowe Rzuty",
            "players": [
                {
                    "fname": "John",
                    "lname": "Moore",
                    "license": "L9791",
                    "age": "43",
                    "gender": "F",
                    "isTeamLeader": true
                },
                {
                    "fname": "John",
                    "lname": "Williams",
                    "license": "L3168",
                    "age": "18",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Chris",
                    "lname": "Davis",
                    "license": "L3581",
                    "age": "46",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "John",
                    "lname": "Miller",
                    "license": "L6838",
                    "age": "21",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Sophia",
                    "lname": "Moore",
                    "license": "L4738",
                    "age": "45",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Olivia",
                    "lname": "Miller",
                    "license": "L7759",
                    "age": "30",
                    "gender": "M",
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Mistrzowie Klasyki",
            "players": [
                {
                    "fname": "Emily",
                    "lname": "Davis",
                    "license": "L9489",
                    "age": "25",
                    "gender": "M",
                    "isTeamLeader": true
                },
                {
                    "fname": "James",
                    "lname": "Miller",
                    "license": "L6546",
                    "age": "23",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Ava",
                    "lname": "Taylor",
                    "license": "L9274",
                    "age": "50",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Sophia",
                    "lname": "Smith",
                    "license": "L8696",
                    "age": "21",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Daniel",
                    "lname": "Smith",
                    "license": "L4830",
                    "age": "36",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Thomas",
                    "license": "L5877",
                    "age": "41",
                    "gender": "F",
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Kule i Stal",
            "players": [
                {
                    "fname": "David",
                    "lname": "Anderson",
                    "license": "L5177",
                    "age": "38",
                    "gender": "M",
                    "isTeamLeader": true
                },
                {
                    "fname": "Olivia",
                    "lname": "Miller",
                    "license": "L9196",
                    "age": "36",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Emma",
                    "lname": "Brown",
                    "license": "L2400",
                    "age": "34",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Chris",
                    "lname": "Johnson",
                    "license": "L2216",
                    "age": "26",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Williams",
                    "license": "L8053",
                    "age": "25",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Emma",
                    "lname": "Moore",
                    "license": "L4951",
                    "age": "45",
                    "gender": "F",
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Słońce Prowansji",
            "players": [
                {
                    "fname": "Daniel",
                    "lname": "Moore",
                    "license": "L3530",
                    "age": "25",
                    "gender": "M",
                    "isTeamLeader": true
                },
                {
                    "fname": "Daniel",
                    "lname": "Moore",
                    "license": "L7605",
                    "age": "45",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Brown",
                    "license": "L8251",
                    "age": "35",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Brown",
                    "license": "L5737",
                    "age": "24",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Emma",
                    "lname": "Smith",
                    "license": "L5452",
                    "age": "29",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Chris",
                    "lname": "Miller",
                    "license": "L6121",
                    "age": "24",
                    "gender": "F",
                    "isTeamLeader": false
                }
            ]
        },
        {
            "team name": "Bouliści",
            "players": [
                {
                    "fname": "Ava",
                    "lname": "Miller",
                    "license": "L5907",
                    "age": "29",
                    "gender": "F",
                    "isTeamLeader": true
                },
                {
                    "fname": "Ava",
                    "lname": "Miller",
                    "license": "L7026",
                    "age": "37",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Michael",
                    "lname": "Williams",
                    "license": "L7350",
                    "age": "35",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Ava",
                    "lname": "Smith",
                    "license": "L8990",
                    "age": "34",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "David",
                    "lname": "Johnson",
                    "license": "L1413",
                    "age": "38",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Olivia",
                    "lname": "Thomas",
                    "license": "L4110",
                    "age": "46",
                    "gender": "F",
                    "isTeamLeader": false
                }
            ]
        }
    ]
}
)";
