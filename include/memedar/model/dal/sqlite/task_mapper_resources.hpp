#ifndef MEMEDAR_MODEL_DAL_TASK_MAPPER_RESOURCES_HPP
#define MEMEDAR_MODEL_DAL_TASK_MAPPER_RESOURCES_HPP


namespace md::model::dal::sqlite {
	class task_index;
	namespace task_resources {
		std::string create_table();

		std::string insert_cmd();
		task_index insert_index();

		std::string select_cmd();
		task_index select_index();

		std::string change_state_cmd();
		task_index change_state_index();

		std::string delete_done_cmd();
		task_index delete_done_index();
	}
}


class md::model::dal::sqlite::task_index
{
public:
	int card_id() const { return m_card_id; }
	int deck_id() const { return m_deck_id; }
	int state()   const { return m_state; }

	void set_card_id(int ind) {  m_card_id = ind; }
	void set_deck_id(int ind) {  m_deck_id = ind; }
	void set_state(int ind)   {  m_state = ind; }
protected:
	int m_card_id = 0;
	int m_deck_id = 0;
	int m_state = 0;
};


#endif // MEMEDAR_MODEL_DAL_TASK_MAPPER_RESOURCES_HPP
