#include "TransferTable.hpp"
#include "Player.hpp"
using namespace std;

TransferTable ::TransferTable()
{
}
void TransferTable::add_new_transfer(shared_ptr<Player> chosen_player, bool should_buy)
{
    pair<shared_ptr<Player>, bool> temp_info;
    temp_info.first = chosen_player;
    temp_info.second = should_buy;
    transfers_informations.push_back(temp_info);
}

void TransferTable::apply_transfers(std ::vector<std ::shared_ptr<Player>> &fantasy_team_players)
{
    for (int index_transfer = 0; index_transfer < transfers_informations.size(); index_transfer++)
    {
        if (transfers_informations[index_transfer].second == BUY)
        {
            fantasy_team_players.push_back(transfers_informations[index_transfer].first);
        }
        else
        {
            for (int index_player = 0; index_player < fantasy_team_players.size(); index_player++)
            {
                if (fantasy_team_players[index_player] == transfers_informations[index_transfer].first)
                {
                    fantasy_team_players.erase(fantasy_team_players.begin() + index_player);
                }
            }
        }
    }
    transfers_informations.clear();
}

void TransferTable::update_needed_posts_after_buy(bool &has_forward, bool &has_goalkeeper, bool &has_midfielder, int &num_defenders, string new_post)
{
    if (new_post == POST_PLAYERS[FW])
    {
        has_forward = true;
    }
    if (new_post == POST_PLAYERS[GK])
    {
        has_goalkeeper = true;
    }
    if (new_post == POST_PLAYERS[MD])
    {
        has_midfielder = true;
    }
    if (new_post == POST_PLAYERS[DF])
    {
        num_defenders++;
    }
}

void TransferTable::update_needed_posts_after_sell(bool &has_forward, bool &has_goalkeeper, bool &has_midfielder, int &num_defenders, string old_post)
{
    if (old_post == POST_PLAYERS[FW])
    {
        has_forward = false;
    }
    if (old_post == POST_PLAYERS[GK])
    {
        has_goalkeeper = false;
    }
    if (old_post == POST_PLAYERS[MD])
    {
        has_midfielder = false;
    }
    if (old_post == POST_PLAYERS[DF])
    {
        num_defenders--;
    }
}

bool TransferTable::find_wanted_player_in_transfer_history(string name)
{
    for (int i = 0; i < transfers_informations.size(); i++)
    {
        if (transfers_informations[i].first->check_name(name))
        {
            transfers_informations.erase(transfers_informations.begin() + i);
            return true;
        }
    }
    return false;
}