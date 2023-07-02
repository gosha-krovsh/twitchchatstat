package twitch

import (
	"fmt"
	"github.com/gempir/go-twitch-irc"
	"github.com/nicklaw5/helix"
	"os"
)

type UpdateResponse struct {
	Plus  int `json:"plus"`
	Minus int `json:"minus"`
}

type User struct {
	UserName      string
	TwitchClient  *twitch.Client
	CurrentUpdate UpdateResponse
}

type APIClient struct {
	clientToUser map[string]map[string]*User // clientID -> userToken -> user
}

func NewAPIClient() *APIClient {
	apiClient := new(APIClient)

	apiClient.clientToUser = make(map[string]map[string]*User)
	return apiClient
}

func (apiClient *APIClient) GetClient(clientId, token string) (*User, bool) {
	if _, ok := apiClient.clientToUser[clientId]; ok {
		if user, ok := apiClient.clientToUser[clientId][token]; ok {
			return user, true
		}
	}
	return nil, false
}

func (apiClient *APIClient) AddClient(clientID, token string) error {
	if _, ok := apiClient.clientToUser[clientID]; !ok {
		apiClient.clientToUser[clientID] = make(map[string]*User)
	}
	if _, ok := apiClient.clientToUser[clientID][token]; !ok {
		user, err := apiClient.createUser(clientID, token)
		if err != nil {
			return err
		}

		apiClient.clientToUser[clientID][token] = user
	}
	return nil
}

func (apiClient *APIClient) createUser(clientID, token string) (*User, error) {
	user := new(User)

	helixClient, err := helix.NewClient(&helix.Options{
		ClientID:        clientID,
		UserAccessToken: token,
	})
	if err != nil {
		return nil, err
	}

	resp, err := helixClient.GetUsers(&helix.UsersParams{})

	if len(resp.Data.Users) == 0 {
		return nil, fmt.Errorf("%s", "invalid credentials")
	}
	responseUser := resp.Data.Users[0]

	user.UserName = responseUser.Login
	user.CurrentUpdate = UpdateResponse{0, 0}
	user.TwitchClient = twitch.NewClient(user.UserName, "oauth:"+token)

	user.TwitchClient.Join(user.UserName)

	user.TwitchClient.OnNewMessage(func(channel string, twitchUser twitch.User, message twitch.Message) {
		if message.Text == "+" {
			user.CurrentUpdate.Plus += 1
			if user.CurrentUpdate.Plus > 10 {
				user.CurrentUpdate.Plus = 10
			}
		} else if message.Text == "-" {
			user.CurrentUpdate.Minus += 1
			if user.CurrentUpdate.Minus > 10 {
				user.CurrentUpdate.Minus = 10
			}
		}
	})

	go func() {
		err = user.TwitchClient.Connect()
		if err != nil {
			_, _ = fmt.Fprint(os.Stderr, err)
		}
	}()

	return user, nil
}
