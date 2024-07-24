#ifndef _TRANSFER_TABLE_HPP_
#define _TRANSFER_TABLE_HPP_
#include <vector>
#include "magic_number.hpp"
#include <memory>
class Player;

class TransferTable
{
public:
    TransferTable();
    void apply_transfers(std ::vector<std ::shared_ptr<Player>> &fantasy_team_players, std ::shared_ptr<Player> &captain);
    void add_new_transfer(std ::shared_ptr<Player> chosen_player, bool should_buy);
    void update_needed_posts_after_buy(bool &has_forward, bool &has_goalkeeper, bool &has_midfielder, int &num_defenders, std ::string new_post);
    void update_needed_posts_after_sell(bool &has_forward, bool &has_goalkeeper, bool &has_midfielder, int &num_defenders, std ::string old_post);
    bool find_wanted_player_in_transfer_history(std ::string name);
    std :: shared_ptr<Player> find_player_ptr_in_transfer_history(std :: string name);
    void save_captain_data(std :: shared_ptr<Player> selected_player);

private:
    std ::vector<std ::pair<std ::shared_ptr<Player>, bool>> transfers_informations;
    std :: shared_ptr<Player> new_captain = NULL;
};

#endif