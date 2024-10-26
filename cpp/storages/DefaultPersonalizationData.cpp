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
                    "age": "1945-03-05",
                    "gender": "M",
                    "isTeamLeader": true
                },
                {
                    "fname": "James",
                    "lname": "Williams",
                    "license": "L3119",
                    "age": "2016-11-12",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "John",
                    "lname": "Anderson",
                    "license": "L4000",
                    "age": "1964-02-29",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Emma",
                    "lname": "Wilson",
                    "license": "L3017",
                    "age": "2007-07-17",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Daniel",
                    "lname": "Davis",
                    "license": "L2472",
                    "age": "1950-01-01",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "John",
                    "lname": "Brown",
                    "license": "L8923",
                    "age": "2000-12-31",
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
                    "age": "1973-04-22",
                    "gender": "M",
                    "isTeamLeader": true
                },
                {
                    "fname": "Emma",
                    "lname": "Thomas",
                    "license": "L1581",
                    "age": "2010-09-09",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Sophia",
                    "lname": "Johnson",
                    "license": "L1022",
                    "age": "1938-06-15",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Thomas",
                    "license": "L3601",
                    "age": "2004-02-28",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Williams",
                    "license": "L1060",
                    "age": "1995-08-13",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Sophia",
                    "lname": "Thomas",
                    "license": "L2403",
                    "age": "1960-12-24",
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
                    "age": "1945-03-17",
                    "gender": "F",
                    "isTeamLeader": true
                },
                {
                    "fname": "David",
                    "lname": "Davis",
                    "license": "L7003",
                    "age": "2017-08-29",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Olivia",
                    "lname": "Johnson",
                    "license": "L7275",
                    "age": "1962-11-05",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Miller",
                    "license": "L2834",
                    "age": "1998-04-12",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "David",
                    "lname": "Brown",
                    "license": "L9907",
                    "age": "2007-12-25",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Chris",
                    "lname": "Anderson",
                    "license": "L4332",
                    "age": "1953-07-02",
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
                    "age": "1979-09-21",
                    "gender": "F",
                    "isTeamLeader": true
                },
                {
                    "fname": "John",
                    "lname": "Williams",
                    "license": "L3168",
                    "age": "2010-01-15",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Chris",
                    "lname": "Davis",
                    "license": "L3581",
                    "age": "1938-05-31",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "John",
                    "lname": "Miller",
                    "license": "L6838",
                    "age": "1986-02-08",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Sophia",
                    "lname": "Moore",
                    "license": "L4738",
                    "age": "2002-11-19",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Olivia",
                    "lname": "Miller",
                    "license": "L7759",
                    "age": "1971-06-23",
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
                    "age": "1945-03-12",
                    "gender": "M",
                    "isTeamLeader": true
                },
                {
                    "fname": "James",
                    "lname": "Miller",
                    "license": "L6546",
                    "age": "1998-11-05",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Ava",
                    "lname": "Taylor",
                    "license": "L9274",
                    "age": "2017-07-28",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Sophia",
                    "lname": "Smith",
                    "license": "L8696",
                    "age": "1962-09-21",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Daniel",
                    "lname": "Smith",
                    "license": "L4830",
                    "age": "1975-04-03",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Thomas",
                    "license": "L5877",
                    "age": "2002-12-25",
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
                    "age": "1989-01-18",
                    "gender": "M",
                    "isTeamLeader": true
                },
                {
                    "fname": "Olivia",
                    "lname": "Miller",
                    "license": "L9196",
                    "age": "1953-06-10",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Emma",
                    "lname": "Brown",
                    "license": "L2400",
                    "age": "2010-02-14",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Chris",
                    "lname": "Johnson",
                    "license": "L2216",
                    "age": "1938-08-29",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Williams",
                    "license": "L8053",
                    "age": "2006-05-19",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Emma",
                    "lname": "Moore",
                    "license": "L4951",
                    "age": "1971-12-31",
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
                    "age": "1944-03-17",
                    "gender": "M",
                    "isTeamLeader": true
                },
                {
                    "fname": "Daniel",
                    "lname": "Moore",
                    "license": "L7605",
                    "age": "2002-11-05",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Brown",
                    "license": "L8251",
                    "age": "1968-07-29",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "James",
                    "lname": "Brown",
                    "license": "L5737",
                    "age": "2016-02-19",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Emma",
                    "lname": "Smith",
                    "license": "L5452",
                    "age": "1955-12-24",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Chris",
                    "lname": "Miller",
                    "license": "L6121",
                    "age": "2008-09-11",
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
                    "age": "1938-05-01",
                    "gender": "F",
                    "isTeamLeader": true
                },
                {
                    "fname": "Ava",
                    "lname": "Miller",
                    "license": "L7026",
                    "age": "2011-04-07",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Michael",
                    "lname": "Williams",
                    "license": "L7350",
                    "age": "1972-01-15",
                    "gender": "F",
                    "isTeamLeader": false
                },
                {
                    "fname": "Ava",
                    "lname": "Smith",
                    "license": "L8990",
                    "age": "1995-08-23",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "David",
                    "lname": "Johnson",
                    "license": "L1413",
                    "age": "2006-10-31",
                    "gender": "M",
                    "isTeamLeader": false
                },
                {
                    "fname": "Olivia",
                    "lname": "Thomas",
                    "license": "L4110",
                    "age": "1983-06-09",
                    "gender": "F",
                    "isTeamLeader": false
                }
            ]
        }
    ]
}
)";
